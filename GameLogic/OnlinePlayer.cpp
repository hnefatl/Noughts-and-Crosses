#include "OnlinePlayer.h"

OnlinePlayer::OnlinePlayer(std::string IP, std::string Port)
	:IP(IP),
	Port(Port)
{

}
OnlinePlayer::~OnlinePlayer()
{

}

std::string OnlinePlayer::Initialise()
{
	// Connect to the server
	if(!Client::Connect(IP, Port))
	{
		return "Failed to connect to the server.";
	}

	return "";
}

std::string OnlinePlayer::GetMove(Move *ChosenMove)
{
	std::string Message;
	Receive(&Message);

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