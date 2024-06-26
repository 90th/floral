#include "DebugConsole/DebugConsole.h"
#include "GlobalData/GlobalData.h"
#include "UI.h"
#include "Drawing.h"
#include "icon.h"

std::unique_ptr<UI> UI::_instance = std::make_unique<UI>();

ID3D11Device* UI::pd3dDevice = nullptr;
ID3D11DeviceContext* UI::pd3dDeviceContext = nullptr;
IDXGISwapChain* UI::pSwapChain = nullptr;
ID3D11RenderTargetView* UI::pMainRenderTargetView = nullptr;

HMODULE UI::hCurrentModule = nullptr;

UI::UI() {
	pd3dDevice = nullptr;
	pd3dDeviceContext = nullptr;
	pSwapChain = nullptr;
	pMainRenderTargetView = nullptr;
	hCurrentModule = nullptr;
}

UI::~UI() {
	CleanupDeviceD3D();
}

bool UI::CreateDeviceD3D(HWND hWnd) {
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	const UINT createDeviceFlags = 0;

	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &pSwapChain, &pd3dDevice, &featureLevel, &pd3dDeviceContext) != S_OK)
		return false;

	CreateRenderTarget();
	return true;
}

void UI::CreateRenderTarget() {
	ID3D11Texture2D* pBackBuffer;
	pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	if (pBackBuffer != nullptr) {
		pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pMainRenderTargetView);
		pBackBuffer->Release();
	}
}

void UI::CleanupRenderTarget() {
	if (pMainRenderTargetView) {
		pMainRenderTargetView->Release();
		pMainRenderTargetView = nullptr;
	}
}

void UI::CleanupDeviceD3D() {
	CleanupRenderTarget();
	if (pSwapChain) {
		pSwapChain->Release();
		pSwapChain = nullptr;
	}

	if (pd3dDeviceContext) {
		pd3dDeviceContext->Release();
		pd3dDeviceContext = nullptr;
	}

	if (pd3dDevice) {
		pd3dDevice->Release();
		pd3dDevice = nullptr;
	}
}

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

LRESULT WINAPI UI::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (pd3dDevice != nullptr && wParam != SIZE_MINIMIZED) {
			CleanupRenderTarget();
			pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
		}
		return 0;

	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;

	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;

	case WM_DPICHANGED:
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports) {
			const RECT* suggested_rect = (RECT*)lParam;
			::SetWindowPos(hWnd, nullptr, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
		}
		break;

	default:
		break;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

inline void UI::CenterWindowOnScreen(HWND hwnd) {
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	POINT clientTopLeft = { clientRect.left, clientRect.top };
	ClientToScreen(hwnd, &clientTopLeft);

	POINT clientBottomRight = { clientRect.right, clientRect.bottom };
	ClientToScreen(hwnd, &clientBottomRight);

	int windowWidth = clientBottomRight.x - clientTopLeft.x;
	int windowHeight = clientBottomRight.y - clientTopLeft.y;

	RECT workArea{};
	SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);

	int centerX = workArea.left + (workArea.right - workArea.left - windowWidth) / 2 - 165;
	int centerY = workArea.top + (workArea.bottom - workArea.top - windowHeight) / 2 - 240;

	SetWindowPos(hwnd, NULL, centerX, centerY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void UI::Render() {
	ImGui_ImplWin32_EnableDpiAwareness();
	HICON hIcon = CreateIconFromResourceEx(icon1, sizeof(icon1), TRUE, 0x00030000, 256, 256, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
	const WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), hIcon, nullptr, nullptr, nullptr, _T("floral"), hIcon };
	::RegisterClassEx(&wc);
	const HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("floral"), WS_OVERLAPPEDWINDOW, 100, 100, 50, 50, NULL, NULL, wc.hInstance, hIcon);

	UI::CenterWindowOnScreen(hwnd);
	GlobalData::GetInstance().setUserData({ "floral", "", "" });
	DebugConsole::GetInstance().OpenConsole();

	if (!CreateDeviceD3D(hwnd)) {
		CleanupDeviceD3D();
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		return;
	}

	::ShowWindow(hwnd, SW_HIDE);
	::UpdateWindow(hwnd);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::DarkStyle();

	ImGui::GetIO().IniFilename = nullptr;

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(pd3dDevice, pd3dDeviceContext);

	const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	bool bDone = false;

	DebugConsole::GetInstance().Print("[Debug] Starting UI loop...");
	while (!bDone) {
		MSG msg;
		while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				bDone = true;
		}

		if (GetAsyncKeyState(VK_END) & 1)
			bDone = true;

		if (bDone)
			break;

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		{
			Drawing::Draw();
		}
		ImGui::EndFrame();

		ImGui::Render();
		const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
		pd3dDeviceContext->OMSetRenderTargets(1, &pMainRenderTargetView, nullptr);
		pd3dDeviceContext->ClearRenderTargetView(pMainRenderTargetView, clear_color_with_alpha);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}

		pSwapChain->Present(1, 0);

#ifndef _WINDLL
		if (!Drawing::isActive())
			break;
#endif
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	::DestroyWindow(hwnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);

#ifdef _WINDLL
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)FreeLibrary, hCurrentModule, NULL, nullptr);
#endif
}