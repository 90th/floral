#include "Drawing.h"
#include "SceneManager.h"

bool Drawing::bDraw = true;

void Drawing::Active() {
	bDraw = true;
}

bool Drawing::isActive() {
	return bDraw == true;
}

void Drawing::Draw() {
	if (isActive()) {
		SceneManager::GetInstance().Render(); // Render the current scene using SceneManager
	}
#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
#endif
}