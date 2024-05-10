#ifndef UI_H
#define UI_H

#include "pch.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class UI
{
private:
	static std::unique_ptr<UI> _instance;

	static ID3D11Device* pd3dDevice;
	static ID3D11DeviceContext* pd3dDeviceContext;
	static IDXGISwapChain* pSwapChain;
	static ID3D11RenderTargetView* pMainRenderTargetView;

	static bool CreateDeviceD3D(HWND hWnd);
	static void CleanupDeviceD3D();
	static void CreateRenderTarget();
	static void CleanupRenderTarget();
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static void CenterWindowOnScreen(HWND hwnd);

public:
	static HMODULE hCurrentModule;

	static void Render();

	UI();
	~UI();

	UI(const UI&) = delete;
	UI& operator = (const UI&) = delete;

	static UI* GetInstance() {
		if (!_instance) {
			_instance = std::make_unique<UI>();
		}
		return _instance.get();
	}
};

#endif
