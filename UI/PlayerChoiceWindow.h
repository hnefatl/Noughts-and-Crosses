#ifndef _PLAYERCHOICEWINDOW_H
#define _PLAYERCHOICEWINDOW_H

#include "Windows\Window.h"

#include <Player.h>
#include <HumanPlayer.h>
#include <AIPlayer.h>
#include <OnlinePlayer.h>

#include <Vector.h>

class PlayerChoiceWindow
	: public Window
{
public:
	virtual void Run();

	Player *PlayerOne;
	Player *PlayerTwo;

protected:
	virtual void Update();
	virtual void Draw();

private:

};

#endif