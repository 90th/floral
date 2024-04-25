#ifndef DRAWING_H
#define DRAWING_H

#include "pch.h"
#include "SceneManager.h"

class Drawing {
private:
	static SceneManager* sceneManager;

public:
	static bool bDraw;

	static void Active();
	static bool isActive();
	//Drawing(SceneManager* manager);
	static void Draw();
};

#endif
