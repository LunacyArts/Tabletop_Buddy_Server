#pragma once
#define User_H

#include <string>
using namespace std;

class User {
	private:
		std::string User_ID;
		std::string FName;
		std::string LName;
		std::string UName;
		std::string Email;
		std::string Creation_Date;
	public:
		User(std::string fn, std::string ln, std::string un, std::string e) {
			FName = fn;
			LName = ln;
			UName = un;
			Email = e;
		}
};