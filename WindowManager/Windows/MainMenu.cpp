#include "../WindowManager.h"
#include "../../DebugConsole/DebugConsole.h"
#include "../../GlobalData/GlobalData.h"
#include "MainMenu.h"
#include "SplashScreen.h"

LPCSTR MainMenu::lpWindowName = "Main menu";
ImVec2 MainMenu::vWindowSize = { 350, 450 };
ImGuiWindowFlags MainMenu::WindowFlags = 0;

void MainMenu::Render() {
	ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(lpWindowName, &Drawing::bDraw, WindowFlags);
	{
		ImGui::Text("Username: %s", GlobalData::GetInstance()->getUserData().username.c_str());
		ImGui::BeginChild("child", ImVec2(200, 200), true); {
			ImGui::Text("This is a child.");
			ImGui::EndChild();
		}
	}
	ImGui::End();
}