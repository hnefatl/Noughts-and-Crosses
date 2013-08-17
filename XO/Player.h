#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include "Move.h"
#include "Grid.h"

class Player
{
public:
	Player();
	virtual ~Player();

	virtual std::string Initialise()=0;
	virtual std::string GetMove(Move *ChosenMove)=0;
	virtual std::string InformMove(Move *ChosenMove)=0;

	Grid *Board;
};

#endif