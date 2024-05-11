#include "SplashScreen.h"
#include "WindowManager.h"
#include "MainMenu.h"

LPCSTR SplashScreen::lpWindowName = "Splash";
ImVec2 SplashScreen::vWindowSize = { 350, 200 }; // Initial window size
ImGuiWindowFlags SplashScreen::WindowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;

inline void drawLoadingAnimation() {
	auto draw = ImGui::GetWindowDrawList();
	ImVec2 pos = ImGui::GetWindowPos();
	ImVec2 center = ImVec2(pos.x + 175, pos.y + 95);

	static ImColor foregroundColor(219, 42, 42);
	static ImColor backgroundColor(54, 53, 58);
	static float arcSize = 0.45f;
	static float radius = 15.f;
	static float thickness = 1.f;

	static float position = 0.f;
	position = ImLerp(position, IM_PI * 2.f, ImGui::GetIO().DeltaTime * 2.3f);

	draw->PathClear();
	draw->PathArcTo(center, radius, 0.f, 2.f * IM_PI, 40.f);
	draw->PathStroke(ImGui::GetColorU32(backgroundColor.Value), 0, thickness);

	draw->PathClear();
	draw->PathArcTo(center, radius, IM_PI * 1.5f + position, IM_PI * (1.5f + arcSize) + position, 40.f);
	draw->PathStroke(ImGui::GetColorU32(foregroundColor.Value), 0, thickness);

	if (position >= IM_PI * 1.90f)
		position = 0.f;
}

void SplashScreen::Render() {
	ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(lpWindowName, &Drawing::bDraw, WindowFlags);
	{
		ImGui::Text("Ready to switch window.");
		drawLoadingAnimation();
		ImGui::Separator();
		if (ImGui::Button("Switch to MainMenu")) {
			WindowManager::GetInstance().SetWindow(std::make_unique<MainMenu>());
		}
	}
	ImGui::End();
}