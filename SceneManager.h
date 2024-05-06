#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include <memory>

class SceneManager {
private:
	std::unique_ptr<Scene> currentScene;

public:
	// Constructor
	SceneManager();

	// Destructor
	~SceneManager();

	// Get a singleton instance of SceneManager
	static SceneManager& GetInstance();

	// Set the current scene
	void SetScene(std::unique_ptr<Scene> scene);

	// Render the current scene
	void Render();
};

#endif // SCENE_MANAGER_H
