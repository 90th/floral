#include "../WindowManager.h"
#include "../../DebugConsole/DebugConsole.h"
#include "../../GlobalData/GlobalData.h"
#include "MainMenu.h"
#include "SplashScreen.h"

LPCSTR MainMenu::lpWindowName = "Main menu";
ImGuiWindowFlags MainMenu::WindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;

void MainMenu::Render() {
	const std::string username = GlobalData::GetInstance().getUserData().username;
	ImGui::SetNextWindowSizeConstraints(ImVec2(350, 490), ImVec2(500, 800)); // Set minimum window size
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(lpWindowName, &Drawing::bDraw, WindowFlags);
	{
		ImGui::Text("Username: %s", username.c_str());
		ImGui::BeginChild("child1", ImVec2(0, 200), true, ImGuiWindowFlags_AlwaysAutoResize);
		{
			ImGui::Text("Child 1");
		}
		ImGui::EndChild();
		ImGui::BeginChild("child2", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysAutoResize);
		{
			ImGui::Text("Child 2");
		}ImGui::EndChild();
	}
	ImGui::End();
}