#pragma once
#define Lobby_H

#include "Character.h"

#include <vector>
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
using namespace std;

class Lobby {
	private:
		//Lobby unique 6 digit ID, DM's lobby name, the ID of the Lobby owner, and lastly the vector containing all the pointers to each lobby
		string lobby_id;
		string lobby_name;
		int GM_ID;
		vector<Character> turn_order;
		
		//Custom sort method for turn_order, return true if second's initiative value is bigger than the first's initiative

	public:
		//lobby constructor: requires an ID, name given by the GM, and ID of the GM
		Lobby(string l_id, string l_name, int gm_id) {
			lobby_id = l_id;
			lobby_name = l_name;
			GM_ID = gm_id;
		}
		
		//adds a character to the vecotr
		void add_char(Character cha) {
			turn_order.push_back(cha);
		}
		
		//reorder turn_order by intiative #
		void init_sort() {
			sort(turn_order.begin(), turn_order.end(), [](Character a, Character b) { return (a.getInitiative()>b.getInitiative()); });
		}
};