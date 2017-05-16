#pragma once
#define User_H

#include <string>
#include <time.h>
using namespace std;

class User {
private:
	string UName;
	string AuthKey;
	time_t LastContact;

public:
	User(string fn, string ln, string un, string e, string pass) {
		string fName = fn;
		string lName = ln;
		UName = un;
		string email = e;
		string password = pass;
	}
	User(string un, string pass) {
		UName = un;
		string password = pass;
	}
};