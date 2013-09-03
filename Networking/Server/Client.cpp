#include "Client.h"

#include "Networking.h"
#include "NetStrings.h"

Client::Client()
	:Run(false),
	Online(false)
{
}
Client::Client(SOCKET Socket)
	:Run(false),
	Socket(Socket),
	Online(true)
{
}
Client::Client(SOCKET Socket, std::string Username)
	:Run(false),
	Socket(Socket),
	Username(Username),
	Online(true)
{

}
Client::~Client()
{
	closesocket(Socket);
}

void Client::Start()
{
	Run=true;
	Receiver=std::thread(&Client::ReceiveConstantly, this);
}

bool Client::Send(std::string Message)
{
	// If client is no longer online
	if(!Online)
	{
		// Return failure
		return false;
	}

	return Net::Send(Socket, Message);
}
bool Client::Receive(std::string *Message)
{
	// If the client is no longer connected
	if(!Online)
	{
		// Return failure
		return false;
	}

	// If a message has been received in the time since last called
	if(Received.size()>0)
	{
		// Store the message
		Received.Lock();
		*Message=Received.front();
		// Remove the message just used from the queue
		Received.pop();
		Received.Unlock();
	}
	else
	{
		// Wait until there is something to receive
		while(Received.size()==0)
		{
			Sleep(500);
		}
		// Receive it (recursive call for neatness)
		return Receive(Message);
	}

	return true;
}

void Client::ReceiveConstantly()
{
	while(Run)
	{
		std::string Temp;
		if(!Net::Receive(Socket, &Temp))
		{
			Online=false;
			break; // Exit the state of constant receiving
		}

		Received.Lock();
		Received.push(Temp);
		Received.Unlock();

		else if(Temp==ServerNotifyingDisconnectionString)
		{
			Online=false;
			break; // Exit the state of constant receiving
		}
	}
}