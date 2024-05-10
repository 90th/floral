#include "WindowManager.h"
#include "SplashScreen.h"
#include "DebugConsole.h"

WindowManager::WindowManager() {}

WindowManager::~WindowManager() {}

WindowManager& WindowManager::GetInstance() {
	static std::unique_ptr<WindowManager> _instance;
	if (!_instance) {
		_instance = std::make_unique<WindowManager>();
		_instance->currentWindow = std::make_unique<SplashScreen>();
	}
	return *_instance;
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