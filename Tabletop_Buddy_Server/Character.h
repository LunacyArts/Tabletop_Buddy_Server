#pragma once
#define Character_H

#include <string>
using namespace std;

class Character {
	private:
		int initiative;
		std::string name;
	public:
		Character(std::string n, int i) {
			initiative = i;
			name = n;
		}

		std::string getname() {
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