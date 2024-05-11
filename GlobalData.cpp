#pragma once
#include "GlobalData.h"

GlobalData* GlobalData::instance = nullptr;

GlobalData* GlobalData::GetInstance() {
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