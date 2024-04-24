#include "MainMenu.h"

LPCSTR MainMenu::lpWindowName = "Main menu";
ImVec2 MainMenu::vWindowSize = { 350, 75 };
ImGuiWindowFlags MainMenu::WindowFlags = 0;

void MainMenu::Render() {
	ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(lpWindowName, &Drawing::bDraw, WindowFlags);
	{
		ImGui::Text("Welcome to the MainMenu!");
	}
	ImGui::End();
}