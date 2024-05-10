#include "SplashScreen.h"
#include "WindowManager.h"
#include "MainMenu.h"

LPCSTR SplashScreen::lpWindowName = "Splash";
ImVec2 SplashScreen::vWindowSize = { 350, 200 }; // Initial window size
ImGuiWindowFlags SplashScreen::WindowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;

void SplashScreen::Render() {
	ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(lpWindowName, &Drawing::bDraw, WindowFlags);
	{
		ImGui::Text("Ready to switch window.");

		if (ImGui::Button("Switch to MainMenu")) {
			WindowManager::GetInstance().SetWindow(std::make_unique<MainMenu>());
		}
	}
	ImGui::End();
}