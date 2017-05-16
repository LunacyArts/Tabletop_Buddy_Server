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
			string FName = fn;
			string LName = ln;
			UName = un;
			string Email = e;
			string Password = pass;
		}


};