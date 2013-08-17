#ifndef _AIPLAYER_H
#define _AIPLAYER_H

#include "Player.h"
#include "Node.h"

#include <string>

class AIPlayer
	: public Player
{
public:
	AIPlayer();
	~AIPlayer();

	std::string Initialise();

	std::string GetMove(Move *ChosenMove);

	std::string InformMove(Grid *NewState);

private:
	Node *Root;
};

#endif