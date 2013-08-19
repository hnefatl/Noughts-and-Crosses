#ifndef _CLIENT_H
#define _CLIENT_H

#include <WS2tcpip.h>
#include <Windows.h>
#include <winsock.h>
#include <string>
#include <queue>
#include <thread>
#include <mutex>

#include "LockableObject.h"

class Client
{
public:
	Client();
	Client(SOCKET Socket);
	Client(SOCKET Socket, std::string Username);
	~Client();

	void Start();

	bool Send(std::string Message);
	bool Receive(std::string *Message);

	SOCKET Socket;
	std::string Username;

	bool Online;
private:
	bool Run;
	std::thread Receiver;
	LockableObject<std::queue<std::string>> Received;
	void ReceiveConstantly();
};

#endif