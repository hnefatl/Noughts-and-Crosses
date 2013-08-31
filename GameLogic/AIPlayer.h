#ifndef _AIPLAYER_H
#define _AIPLAYER_H

#include "Player.h"
#include "Node.h"

#include <string>

class Frame
{
public:
	Frame();
	Frame(Node *Current, CellContents CurrentPlayer)
		:Current(Current),
		CurrentPlayer(CurrentPlayer)
	{
	}

	Node *Current;
	CellContents CurrentPlayer;
};

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
	void GenerateTree(Node *Current, CellContents CurrentPlayer);

	Node *Root;
};

#endif