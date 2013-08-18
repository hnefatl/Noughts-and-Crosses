#ifndef _GAME_H
#define _GAME_H

#include "Client.h"
#include <vector>

class Game
{
public:
	Game();
	Game(Client *PlayerOne, Client *PlayerTwo);

	void Play();
	bool IsPlaying();



private:
	std::vector<Client *> Players;
	
	bool Playing;
};

#endif