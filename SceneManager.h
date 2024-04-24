#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"

// Class for managing scenes and rendering the current scene
class SceneManager {
private:

	Scene* currentScene;

public:
	SceneManager();

	void SetScene(Scene* scene);

	void Render();
};

#endif
