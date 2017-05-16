#pragma once
#define Server_H

#include "Lobby.h"
#include "User.h"
#include "Character.h"
#include "ServerComms.h"

#include <vector>
#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <thread>
#include <windows.h>
using namespace std;

//Core Server creation for Tabletop_Buddy. Takes not arguments, generates Server Object and starts running.
class Server {
	private:
		vector<Lobby> Lobby_List;
		vector<User> Current_Users;
		const string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		int numChar = sizeof(digits) - 1;

	public:
		//Server boot
		Server() {
			ServerComms sc(L"http://localhost:9000/");
			sc.start_server();
			cout << "Server listener started.\n";
			//Set up random server seed
			srand(time(NULL));
			cout << "Random seed genrated for Lobby IDs.\n";
			this->RunServer();
		}
		//Server running loop
		void Server::RunServer() {
			while (1) {
				cout << "Server is still running.\n";
				//1 Second wait to reproduce confirmation server is running.
				Sleep(1000);
			}
		}
		//Lobby creation, requires a name and gm_id to create a lobby, generates a 6 digit pin using get_key(), then pushes it into vector turn_order
		string create_lobby(string l_name, int gm_id) {
			//generate 6 digit key
			string key = Server::get_key();
			//cout to server cmd window
			cout << "Starting new server with key: " << key << "\n";
			//creates lobby and adds it to the turn_oder vector
			Lobby_List.push_back(Lobby(key, l_name, gm_id));
			//cout to server cmd window completion
			cout << "Lobby Startedwith key, " << key << ", and name of, " << l_name << ", for GM, " << gm_id << "\n";
			return key;
		}
		//Close out a Lobby using Lobby_ID
		void close_lobby(std::string id) {
		
		}
		//Generate a Lobby_ID
		string get_key() {
			string id = "";
			for (int i = 0; i < 6; i++) {
				id = id + digits[rand() % numChar];
			}
			cout << "The ID is: " << id << "\n";
			return id;
		}
};