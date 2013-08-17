#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include "Move.h"

class Player
{
public:
	virtual std::string Initialise()=0;
	virtual std::string GetMove(Move *ChosenMove)=0;
	virtual std::string InformMove(Move *ChosenMove)=0;
};

#endif