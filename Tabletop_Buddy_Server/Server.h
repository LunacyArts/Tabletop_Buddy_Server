#pragma once
#define Server_H

#include "Lobby.h"
#include "Character.h"
#include "ServerComms.h"

#include <vector>
#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <thread>
using namespace std;

class Server {
	private:
		std::vector<Lobby> Lobby_List;
		const std::string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		int numChar = sizeof(digits) - 1;

	public:
		//Server boot
		Server() {
			ServerComms sc(L"http://localhost:9000/");
			sc.start_server();
			std::cout << "Server started.\n";
			//Set up random server seed
			srand(time(NULL));
			while (1) {}
		}

		//Lobby creation, requires a name and gm_id to create a lobby, generates a 6 digit pin using get_key(), then pushes it into vector turn_order
		std::string create_lobby(std::string l_name, int gm_id) {
			//generate 6 digit key
			std::string key = Server::get_key();
			//cout to server cmd window
			std::cout << "Starting new server with key: " << key << "\n";
			//creates lobby and adds it to the turn_oder vector
			Lobby_List.push_back(Lobby(key, l_name, gm_id));
			//cout to server cmd window completion
			std::cout << "Lobby Startedwith key, " << key << ", and name of, " << l_name << ", for GM, " << gm_id << "\n";
			return key;
		}

		void close_lobby(std::string id) {

		}

		std::string get_key() {
			std::string id = "";
			for (int i = 0; i < 6; i++) {
				id = id + digits[rand() % numChar];
			}
			std::cout << "The ID is: " << id << "\n";
			return id;
		}
};