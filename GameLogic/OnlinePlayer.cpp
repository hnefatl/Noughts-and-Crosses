#include "OnlinePlayer.h"

#include <NetStrings.h>
#include <sstream>

OnlinePlayer::OnlinePlayer()
	:Player(PlayerType::Online)
{

}
OnlinePlayer::~OnlinePlayer()
{

}

void OnlinePlayer::SetData(std::string IP, std::string Port)
{
	this->IP=IP;
	this->Port=Port;
}

std::string OnlinePlayer::Initialise()
{
	// Connect to the server
	if(!Connect(IP, Port))
	{
		return "Failed to connect to the server.";
	}

	// Wait for other player to connect
	std::string Message;
	Receive(&Message);

	// If the message isn't that a client has connected
	if(Message!=ServerNotifyingConnectionString)
	{
		// Return an error
		return "Failed to connect to the opponent.";
	}

	// Receive the turn number
	if(!Receive(&Message))
	{
		return "Opponent disconnected.";
	}
	std::stringstream Stream;
	Stream<<Message;
	unsigned int PlayerNumber;
	Stream>>PlayerNumber;
	PlayerSymbol=(CellContents)PlayerNumber;

	return "";
}

std::string OnlinePlayer::GetMove(Move *ChosenMove)
{
	std::string Message;
	if(!Receive(&Message))
	{
		return "Opponent disconnected.";
	}

	// Convert our received string to a move
	if(!Move::Parse(&Message, ChosenMove))
	{
		return "Parsing failed.";
	}
	
	return "";
}

std::string OnlinePlayer::InformMove(Grid *NewState)
{
	std::string Representation;
	if(!Grid::GetString(NewState, &Representation))
	{
		return "Failed to get string representation from received data.";
	}

	if(!Send(Representation))
	{
		return "Failed to send data.";
	}

	return "";
}