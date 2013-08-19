#ifndef _ONLINEPLAYER_H
#define _ONLINEPLAYER_H

#include "Player.h"
#include "Client.h"

class OnlinePlayer
	: public Player, public Client
{
public:
	OnlinePlayer();
	~OnlinePlayer();

	void SetData(std::string IP, std::string Port);

	std::string Initialise();

	std::string GetMove(Move *ChosenMove);

	std::string InformMove(Grid *NewState);

protected:
	std::string IP, Port;
};

#endif