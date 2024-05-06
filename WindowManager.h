#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "Window.h"
#include <memory>

class WindowManager {
private:
	std::unique_ptr<Window> currentWindow;

public:
	// Constructor
	WindowManager();

	// Destructor
	~WindowManager();

	// Get a singleton instance of WindowManager
	static WindowManager& GetInstance();

	// Set the current window
	void SetWindow(std::unique_ptr<Window> window);

	// Render the current window
	void Render();
};

#endif // WINDOW_MANAGER_H
