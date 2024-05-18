#include "WindowManager.h"
#include "Windows/SplashScreen.h"

WindowManager::WindowManager() : hwnd(nullptr) {}

WindowManager::~WindowManager() {}

WindowManager& WindowManager::GetInstance() {
	static WindowManager instance;
	if (!instance.currentWindow) {
		instance.currentWindow = std::make_unique<SplashScreen>();
	}
	return instance;
}

void WindowManager::SetWindow(std::unique_ptr<Window> window) {
	currentWindow.reset();
	currentWindow = std::move(window);
}

void WindowManager::Render() {
	if (currentWindow) {
		currentWindow->Render();
	}
}