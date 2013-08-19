#include "Client.h"

#include "Networking.h"

bool Client::Connect(std::string IP, std::string Port)
{
	WSAData Data;

	if(WSAStartup(MAKEWORD(1, 1), &Data)!=0)
	{
		return false;
	}

	addrinfo *ServerInfo, Hints;

	memset(&Hints, 0, sizeof(Hints));
	Hints.ai_family=AF_UNSPEC;
	Hints.ai_socktype=SOCK_STREAM;

	int Rcv;
	if((Rcv=getaddrinfo(IP.c_str(), Port.c_str(), &Hints, &ServerInfo))!=0)
	{
		return false;
	}

	addrinfo *p=NULL;
	for(p=ServerInfo; p!=NULL; p=ServerInfo->ai_next)
	{
		if((ServerSocket=socket(p->ai_family, p->ai_socktype, p->ai_protocol))==-1)
		{
			continue;
		}

		if(connect(ServerSocket, p->ai_addr, p->ai_addrlen)==-1)
		{
			continue;
		}

		break;
	}
	if(p!=NULL)
	{
		return false;
	}

	freeaddrinfo(ServerInfo);
	return true;
}

bool Client::Send(std::string Message)
{
	return Net::Send(ServerSocket, Message);
}
bool Client::Receive(std::string *Buffer)
{
	return Net::Receive(ServerSocket, Buffer);
}