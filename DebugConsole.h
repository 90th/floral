#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <mutex>

class DebugConsole {
public:
	static DebugConsole& Instance() {
		static DebugConsole instance;
		return instance;
	}

	void OpenConsole() {
		std::lock_guard<std::mutex> lock(mutex_);
		if (!consoleAllocated) {
			AllocConsole();
			system("title [Debug Console] - Floral");
			freopen_s(&consoleOut, "CONOUT$", "w", stdout);
			consoleAllocated = true;
		}
	}

	void Print(const std::string& message) {
		std::lock_guard<std::mutex> lock(mutex_);
		if (!consoleAllocated)
			OpenConsole();
		std::cout << message << std::endl;
	}

	void Clear() {
		std::lock_guard<std::mutex> lock(mutex_);
		system("cls");
	}

private:
	DebugConsole() : consoleOut(nullptr), consoleAllocated(false) {}

	~DebugConsole() {
		std::lock_guard<std::mutex> lock(mutex_);
		if (consoleAllocated)
			FreeConsole();
	}

	FILE* consoleOut;
	bool consoleAllocated;
	std::mutex mutex_;
};
