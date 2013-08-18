#ifndef _GAME_H
#define _GAME_H

#include "Client.h"
#include <vector>

#include "Grid.h"
#include <thread>

class Game
{
public:
	Game();
	Game(Client *PlayerOne, Client *PlayerTwo);
	~Game();

	void Play();
	bool IsPlaying();

private:
	void _Play();
	std::vector<Client *> Players;
	
	Grid Board;

	bool Playing;
	std::thread PlayingThread;
};

#endif