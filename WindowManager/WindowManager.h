#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "Window.h"
#include <memory>
#include <Windows.h>

class WindowManager {
private:
	std::unique_ptr<Window> currentWindow;
	HWND hwnd;
public:
	WindowManager();
	~WindowManager();
	static WindowManager& GetInstance();
	void SetWindow(std::unique_ptr<Window> window);
	void Render();
	HWND GetHwnd() const { return hwnd; }
};

#endif // WINDOW_MANAGER_H
