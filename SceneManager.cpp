#include "SceneManager.h"
#include "MainMenu.h" // Include your scene headers as needed

SceneManager::SceneManager() : currentScene(std::make_unique<MainMenu>()) {}

SceneManager::~SceneManager() {}

SceneManager& SceneManager::GetInstance() {
	static SceneManager instance;
	return instance;
}

void SceneManager::SetScene(std::unique_ptr<Scene> scene) {
	currentScene.reset();
	currentScene = std::move(scene);
}

void SceneManager::Render() {
	if (currentScene) {
		currentScene->Render();
	}
}