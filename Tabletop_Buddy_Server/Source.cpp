#include "Character.h"
#include "Lobby.h"
#include "Server.h"

#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
using namespace std;


int main(int argc, char *argv[]) {
	
	std::cout << "Starting Server.\n";
	Server server = Server();
	cout << "Server has been closed. Stopping executable.";
	Sleep(5000);
	return 0;

}