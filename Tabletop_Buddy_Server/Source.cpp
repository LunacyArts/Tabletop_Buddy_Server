#include "Character.h"
#include "Lobby.h"
#include "Server.h"

#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
using namespace std;


int main(int argc, char *argv[]) {
	
	std::cout << "Starting Server\n";
	Server server = Server();
	std::string Lobby_ID = server.create_lobby("Temp", 0000);
	thread RunServer(&Server::RunServer, server);
	while (1) 
	{
		cout << "hello \n";
		Sleep(5);
	};
	return 0;

}