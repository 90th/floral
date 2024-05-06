#include "Drawing.h"
#include "WindowManager.h"

bool Drawing::bDraw = true;

void Drawing::Active() {
	bDraw = true;
}

bool Drawing::isActive() {
	return bDraw == true;
}

void Drawing::Draw() {
	if (isActive()) {
		WindowManager::GetInstance().Render(); // Render the current window using WindowManager
	}
#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
#endif
}