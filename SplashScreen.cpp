#include "SplashScreen.h"
#include <windows.h>

LPCSTR SplashScreen::lpWindowName = "Splash";
ImVec2 SplashScreen::vWindowSize = { 350, 450 }; // Initial window size
ImGuiWindowFlags SplashScreen::WindowFlags = 0;

void SplashScreen::Render() {
	ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(lpWindowName, &Drawing::bDraw, WindowFlags);
	{
		ImGui::Text("Splash Screen");
		ImGui::Text("Version 1.0.0");
		ImGui::Text("Ready to switch scenes.");
	}
	ImGui::End();
}