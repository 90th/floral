#include "Drawing.h"

bool Drawing::bDraw = true;
SceneManager* Drawing::sceneManager = new SceneManager();

void Drawing::Active()
{
	bDraw = true;
}

bool Drawing::isActive()
{
	return bDraw == true;
}

void Drawing::Draw()
{
	if (isActive() && sceneManager != nullptr)
	{
		sceneManager->Render();
	}

#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
#endif
}