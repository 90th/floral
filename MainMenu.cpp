#include "MainMenu.h"
#include "SceneManager.h"
#include "SplashScreen.h"

LPCSTR MainMenu::lpWindowName = "Main menu";
ImVec2 MainMenu::vWindowSize = { 350, 450 };
ImGuiWindowFlags MainMenu::WindowFlags = 0;

void MainMenu::Render() {
	ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(lpWindowName, &Drawing::bDraw, WindowFlags);
	{
		ImGui::Text("Main menu");

		// Debug text to ensure this part of code is reached
		ImGui::Text("Ready to switch scenes.");

		if (ImGui::Button("Switch to Splash Screen")) {
			// Set the scene to SplashScreen
			SceneManager::GetInstance().SetScene(std::make_unique<SplashScreen>());
		}

		// Additional debugging information can go here
	}
	ImGui::End();
}