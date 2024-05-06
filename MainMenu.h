#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Window.h"
#include "pch.h"
#include "Drawing.h"

// Class for rendering the main menu scene
class MainMenu : public Window {
private:
	static LPCSTR lpWindowName;
	static ImVec2 vWindowSize;
	static ImGuiWindowFlags WindowFlags;

public:
	// Renders the main menu UI
	void Render() override;
};

#endif