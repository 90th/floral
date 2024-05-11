#include "MainMenu.h"
#include "DebugConsole.h"
#include "WindowManager.h"
#include "SplashScreen.h"
#include "GlobalData.h"

LPCSTR MainMenu::lpWindowName = "Main menu";
ImVec2 MainMenu::vWindowSize = { 350, 450 };
ImGuiWindowFlags MainMenu::WindowFlags = 0;

void MainMenu::Render() {
	ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(lpWindowName, &Drawing::bDraw, WindowFlags);
	{
		ImGui::Text("Username: %s", GlobalData::GetInstance()->getUserData().username.c_str());
	}
	ImGui::End();
}