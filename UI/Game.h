#ifndef _GAME_H
#define _GAME_H

#include <Player.h>
#include <HumanPlayer.h>
#include <OnlinePlayer.h>
#include <AIPlayer.h>

#include <vector>
#include <string>

class Game
{
public:
	Game();

	void Play();

private:
	std::vector<Player *> Players;
};

#endif