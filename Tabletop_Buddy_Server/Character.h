#pragma once
#define Character_H

#include <string>
using namespace std;

class Character {
	private:
		int initiative;
		string name;
	public:
		Character(string n, int i) {
			initiative = i;
			name = n;
		}

		string getname() {
			return name;
		}

		int getInitiative() {
			return initiative;
		}

		void deleteChar() {
			Character::~Character();
		}

		~Character() {}
	protected:
};