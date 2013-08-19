#include "Server.h"

#include "Networking.h"

Server::Server()
	:Run(false)
{

}

bool Server::Start(std::string IP, std::string Port, unsigned int Backlog)
{
	this->IP=IP;
	this->Port=Port;
	this->Backlog=Backlog;
	Run=true;

	Bind();
	Listen();

	while(Run)
	{
		// Accept a new client
		Clients.push_back(Accept());

		// Cull all dead clients
		for(unsigned int x=0; x<Clients.size(); x++)
		{
			if(!Clients[x]->Online)
			{
				// Remove the client
				Clients.erase(Clients.begin()+x);
			}
		}

		// If there are 2 or more players
		if(Clients.size()>=2)
		{
			// Create the players
			Client *PlayerOne=Clients[0];
			Client *PlayerTwo=Clients[1];
			// Create the game
			Game *NewGame=new Game(PlayerOne, PlayerTwo);
			// Store the game
			Games.push_back(NewGame);
			// Remove the clients
			Clients.erase(Clients.begin(), Clients.begin()+1);
			// Start the game
			NewGame->Play();

			// Cull all dead games
			for(unsigned int x=0; x<Games.size(); x++)
			{
				// Finished playing
				if(!Games[x]->IsPlaying())
				{
					Games.erase(Games.begin()+x);
				}
			}
		}
	}

	return true;
}

bool Server::Bind()
{
	WSAData Data;

	if(WSAStartup(MAKEWORD(1, 1), &Data)!=0)
	{
		return false;
	}

	addrinfo Hints, *ServerInfo;

	memset(&Hints, 0, sizeof(Hints));
	Hints.ai_family=AF_INET;
	Hints.ai_socktype=SOCK_STREAM;
	Hints.ai_protocol=IPPROTO_TCP;
	Hints.ai_flags=AI_PASSIVE;

	int Rcv;
	if((Rcv=getaddrinfo(NULL, Port.c_str(), &Hints, &ServerInfo))!=0)
	{
		return false;
	}

	char yes=1;
	addrinfo *p;
	for(p=ServerInfo; p!=NULL; p=p->ai_next)
	{
		if((ServerSocket=socket(p->ai_family, p->ai_socktype, p->ai_protocol))==-1)
		{
			continue;
		}

		if(setsockopt(ServerSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))==-1)
		{
			return false;
		}

		if(bind(ServerSocket, p->ai_addr, p->ai_addrlen)==-1)
		{
			closesocket(ServerSocket);
			continue;
		}

		break;
	}

	if(p==NULL)
	{
		return false;
	}

	freeaddrinfo(ServerInfo);

	return true;
}

bool Server::Listen()
{
	if(!listen(ServerSocket, Backlog))
	{
		return false;
	}

	return true;
}

Client *Server::Accept()
{
	Client *Temp=new Client();
	sockaddr_storage Storage;
	socklen_t Size=sizeof(Storage);

	while(Run)
	{
		Temp->Socket=accept(ServerSocket, (sockaddr *)&Storage, &Size);
		if(Temp->Socket!=-1)
		{
			break;
		}
	}

	if(!Net::Receive(Temp->Socket, &Temp->Username))
	{
		return false;
	}

	return Temp;
}