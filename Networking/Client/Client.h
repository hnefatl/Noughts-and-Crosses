#ifndef _CLIENT_H
#define _CLIENT_H

#include <string>

#include <WS2tcpip.h>
#include <Windows.h>
#include <winsock.h>

class Client
{
public:
	Client();

	bool Connect(std::string IP, std::string Port);

	bool Send(std::string Message);
	bool Receive(std::string *Buffer);

private:
	SOCKET Socket;
	SOCKET ServerSocket;
};

#endif