#ifndef _SERVER_H
#define _SERVER_H

#include <string>
#include <vector>

#include <WS2tcpip.h>
#include <Windows.h>
#include <winsock.h>

#include "Client.h"
#include "Game.h"

class Server
{
public:
	Server();

	bool Start(std::string IP, std::string Port, unsigned int Backlog);

	bool Bind();

	bool Listen();

	Client *Accept();

private:
	SOCKET ServerSocket;

	std::vector<Client *> Clients;
	std::vector<Game *> Games;

	std::string IP, Port;
	unsigned int Backlog;
	bool Run;
};

#endif