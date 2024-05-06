#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include "Window.h"
#include "pch.h"
#include "Drawing.h"

// Class for rendering the splash scene
class SplashScreen : public Window {
private:
	static LPCSTR lpWindowName;
	static ImVec2 vWindowSize;
	static ImGuiWindowFlags WindowFlags;

public:
	// Renders the splash UI
	void Render() override;
};

#endif
