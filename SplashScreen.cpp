#include "SplashScreen.h"
#include "SceneManager.h"
#include "MainMenu.h"

LPCSTR SplashScreen::lpWindowName = "Splash";
ImVec2 SplashScreen::vWindowSize = { 350, 450 }; // Initial window size
ImGuiWindowFlags SplashScreen::WindowFlags = 0;

void SplashScreen::Render() {
	ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(lpWindowName, &Drawing::bDraw, WindowFlags);
	{
		// Debug text to ensure this part of code is reached
		ImGui::Text("Ready to switch scenes.");

		if (ImGui::Button("Switch to MainMenu")) {
			// Set the scene to SplashScreen
			SceneManager::GetInstance().SetScene(std::make_unique<MainMenu>());
		}
	}
	ImGui::End();
}