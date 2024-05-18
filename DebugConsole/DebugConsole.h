#pragma once

#include <iostream>
#include <string_view>
#include <Windows.h>
#include <mutex>

class DebugConsole {
public:
	static DebugConsole& GetInstance() {
		static DebugConsole instance;
		return instance;
	}

	void OpenConsole() {
		std::lock_guard<std::mutex> lock(mutex_);
		if (!consoleAllocated) {
			if (AllocConsole()) {
				system("title [Debug Console] - Floral");
				freopen_s(&consoleOut, "CONOUT$", "w", stdout);
				consoleAllocated = true;
			}
		}
	}

	void Print(std::string_view message) {
		std::lock_guard<std::mutex> lock(mutex_);
		if (!consoleAllocated)
			OpenConsole();
		std::cout.write(message.data(), message.size());
		std::cout.flush();
	}

	void Clear() {
		std::lock_guard<std::mutex> lock(mutex_);
		if (consoleAllocated) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(hConsole, &csbi);
			DWORD written;
			FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X * csbi.dwSize.Y, { 0, 0 }, &written);
			FillConsoleOutputAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, csbi.dwSize.X * csbi.dwSize.Y, { 0, 0 }, &written);
			SetConsoleCursorPosition(hConsole, { 0, 0 });
		}
	}
private:
	DebugConsole() {}
	~DebugConsole() {
		std::lock_guard<std::mutex> lock(mutex_);
		if (consoleAllocated)
			FreeConsole();
	}

	FILE* consoleOut;
	bool consoleAllocated;
	std::mutex mutex_;
};