#ifndef _GAMEWINDOW_H
#define _GAMEWINDOW_H

#include "Window.h"

#include <vector>
#include <Globals.h>

#include <Player.h>
#include <HumanPlayer.h>
#include <OnlinePlayer.h>
#include <AIPlayer.h>

#include <Move.h>
#include <Grid.h>

class GameWindow
	: public Window
{
public:
	GameWindow();

	virtual bool Run();

protected:
	virtual UpdateResult Update();
	virtual void Draw(bool Initial=false);

	void PrintError(std::string Error, std::string Additional="");

	Grid *Board;

	std::vector<Player *> Players;
	unsigned int CurrentPlayer;

	Move *LatestMove;
};

#endif