#include "SceneManager.h"
#include "SplashScreen.h"
#include "DebugConsole.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

SceneManager& SceneManager::GetInstance() {
	static std::unique_ptr<SceneManager> _instance;
	if (!_instance) {
		_instance = std::make_unique<SceneManager>();
		// Initialize with default scene, for example:
		_instance->currentScene = std::make_unique<SplashScreen>();
	}
	return *_instance;
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