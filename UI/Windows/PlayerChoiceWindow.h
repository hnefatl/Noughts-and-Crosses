#ifndef _PLAYERCHOICEWINDOW_H
#define _PLAYERCHOICEWINDOW_H

#include "Window.h"

#include <Player.h>
#include <HumanPlayer.h>
#include <AIPlayer.h>
#include <OnlinePlayer.h>
#include <Vector.h>

#include <vector>
#include <string>

class Column
{
public:
	Column();
	Column(std::string Title, Vector Position);

	std::string Title;
	Vector Position;
	std::vector<std::string> Contents;
	unsigned int CurrentSelection, PreviousSelection;

	void ChangeSelection(unsigned int NewSelection);

	void Draw(bool Selected);
	void DrawTitle(bool Selected);
	void DrawContent(unsigned int ContentNumber, bool Selected);

	void Update();
};

class PlayerChoiceWindow
	: public Window
{
public:
	PlayerChoiceWindow();

	virtual bool Run();

	Player *PlayerOne;
	Player *PlayerTwo;

protected:
	virtual UpdateResult Update();
	virtual void Draw(bool Initial=false);

	void GetPlayersFromSelection();

	unsigned int CurrentColumn, PreviousColumn;

	std::vector<Column> Columns;
};

#endif