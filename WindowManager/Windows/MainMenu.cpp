#include "../WindowManager.h"
#include "../../DebugConsole/DebugConsole.h"
#include "../../GlobalData/GlobalData.h"
#include "MainMenu.h"
#include "SplashScreen.h"

LPCSTR MainMenu::lpWindowName = "Main menu";
ImGuiWindowFlags MainMenu::WindowFlags = 0;

void MainMenu::Render() {
	ImGui::SetNextWindowSizeConstraints(ImVec2(350, 450), ImVec2(FLT_MAX, FLT_MAX)); // Set minimum window size
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(lpWindowName, &Drawing::bDraw, WindowFlags);
	{
		ImGui::Text("Username: %s", GlobalData::GetInstance()->getUserData().username.c_str());

		ImGui::BeginChild("child1", ImVec2(0, 200), true, ImGuiWindowFlags_AlwaysAutoResize);
		{
			ImGui::Text("Child 1");
		}
		ImGui::EndChild();

		ImGui::BeginChild("child2", ImVec2(0, 200), true, ImGuiWindowFlags_AlwaysAutoResize);
		{
			ImGui::Text("Child 2");
		}
		ImGui::EndChild();
	}
	ImGui::End();
}