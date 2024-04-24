#include "MainMenu.h"

LPCSTR MainMenu::lpWindowName = "ImGui Standalone";
ImVec2 MainMenu::vWindowSize = { 350, 75 };
ImGuiWindowFlags MainMenu::WindowFlags = 0;

void MainMenu::Render() {
	ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(lpWindowName, &Drawing::bDraw, WindowFlags);
	{
		ImGui::Text("Create your own menu.");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
	ImGui::End();
}