#include "GlobalData.h"

std::mutex GlobalData::mutex;
std::unique_ptr<GlobalData> GlobalData::instance = nullptr;

GlobalData& GlobalData::GetInstance() {
	std::lock_guard<std::mutex> lock(mutex);
	if (!instance) { // Check if instance is null
		instance = std::make_unique<GlobalData>(); // Create a new instance
	}
	return *instance; // Return the instance
}

GlobalData::UserData GlobalData::getUserData() const {
	return GetInstance().userData; // Access userData through GetInstance
}

void GlobalData::setUserData(const UserData& newData) {
	GetInstance().userData = newData;
}

GlobalData::SystemData GlobalData::getSystemData() const {
	return GetInstance().systemData; // Access systemData through GetInstance
}

void GlobalData::setSystemData(const SystemData& newData) {
	GetInstance().systemData = newData;
}