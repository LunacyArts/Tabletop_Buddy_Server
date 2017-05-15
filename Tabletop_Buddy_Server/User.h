#pragma once
#define User_H

#include <string>
using namespace std;

class User {
	private:
		string User_ID;
		string FName;
		string LName;
		string UName;
		string Email;
		string Creation_Date;
	public:
		User(string fn, string ln, string un, string e) {
			FName = fn;
			LName = ln;
			UName = un;
			Email = e;
		}
};