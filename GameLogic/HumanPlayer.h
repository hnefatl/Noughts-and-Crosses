#ifndef _HUMANPLAYER_H
#define _HUMANPLAYER_H

#include "Player.h"

class HumanPlayer
	: public Player
{
public:
	HumanPlayer();
	~HumanPlayer();

	std::string Initialise();

	std::string GetMove(Move *ChosenMove);

	std::string InformMove(Grid *NewState);

private:
	
};

#endif