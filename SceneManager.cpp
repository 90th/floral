#include "SceneManager.h"
#include "SplashScreen.h" // Include your scene headers as needed

SceneManager::SceneManager() : currentScene(std::make_unique<SplashScreen>()) {}

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