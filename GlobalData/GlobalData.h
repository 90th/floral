#pragma once
#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <string>
#include <mutex>
#include <memory> // Added for smart pointers

class GlobalData {
private:
	static std::mutex mutex;
	static std::unique_ptr<GlobalData> instance; // Use a smart pointer
	struct UserData {
		std::string username;
		std::string email;
		std::string ipAddress;
	} userData;

	struct SystemData {
		// add system related data in the future.
	} systemData;

public:
	GlobalData() {} // Private constructor to prevent external instantiation

	static GlobalData& GetInstance();

	// methods for user data
	UserData getUserData() const;
	void setUserData(const UserData& newData);

	// methods for system data
	SystemData getSystemData() const;
	void setSystemData(const SystemData& newData);
};

#endif // GLOBALDATA_H