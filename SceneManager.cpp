#include "SceneManager.h"
#include "MainMenu.h"

SceneManager::SceneManager() : currentScene(new MainMenu()) {}

void SceneManager::SetScene(Scene* scene) {
	currentScene = scene;
}

void SceneManager::Render() {
	if (currentScene) {
		currentScene->Render();
	}
}