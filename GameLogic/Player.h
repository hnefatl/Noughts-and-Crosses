#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>

#include "Move.h"
#include "Grid.h"

#include "PlayerType.h"

class Player
{
public:
	Player(PlayerType Type);
	virtual ~Player();

	virtual std::string Initialise()=0;
	virtual std::string GetMove(Move *ChosenMove)=0;
	virtual std::string InformMove(Grid *NewState)=0;

	PlayerType Type;
};

#endif