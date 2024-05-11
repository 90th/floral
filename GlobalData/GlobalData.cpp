#include "GlobalData.h"

GlobalData* GlobalData::instance = nullptr;
std::mutex GlobalData::mutex;

GlobalData* GlobalData::GetInstance() {
	std::lock_guard<std::mutex> lock(mutex);
	if (!instance)
		instance = new GlobalData();
	return instance;
}

GlobalData::UserData GlobalData::getUserData() const {
	return userData;
}

void GlobalData::setUserData(const UserData& newData) {
	userData = newData;
}

GlobalData::SystemData GlobalData::getSystemData() const {
	return systemData;
}

void GlobalData::setSystemData(const SystemData& newData) {
	systemData = newData;
}