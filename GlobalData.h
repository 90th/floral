#pragma once
#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <string>

class GlobalData {
private:
	static GlobalData* instance;
	GlobalData() {}

public:
	struct UserData {
		std::string username;
		std::string email;
		std::string ipAddress;
	}userData;

	struct SystemData {
		// add system related data in the future.
	} systemData;

	static GlobalData* GetInstance();

	// Methods for user data
	UserData getUserData() const;
	void setUserData(const UserData& newData);

	// Methods for system data
	SystemData getSystemData() const;
	void setSystemData(const SystemData& newData);
};

#endif // GLOBALDATA_H
