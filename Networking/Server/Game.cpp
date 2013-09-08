#include "Game.h"

#include <sstream>

#include "NetStrings.h"
#include "Globals.h"

#include <CellContents.h>
#include <Grid.h>
#include <Move.h>

Game::Game()
	:Playing(true)
{
}
Game::Game(Client *PlayerOne, Client *PlayerTwo)
	:Playing(true)
{
	Players.push_back(PlayerOne);
	Players.push_back(PlayerTwo);
}
Game::~Game()
{
	for(unsigned int x=0; x<Players.size(); x++)
	{
		delete Players[x];
	}
	Players.clear();
}

void Game::Play()
{
	// Start the game on a new thread
	PlayingThread=std::thread(&Game::_Play, this);
}

void Game::_Play()
{
	/*
	The structure of the game is thus:
	Pre-step. Initialise each Client, sending them a 0 or a 1 to symbolise whether they are an X or a O

	1. Send a message to PlayerOne informing it that it is its go.
	2. Receive a message from PlayerOne informing the server of the move taken.
	3. Send a message to PlayerOne and PlayerTwo informing them of the move taken
	4. Send a message to PlayerTwo informing it that it is its go
	5. Receive a message from PlayerTwo informing the server of the move taken
	6. Send a message to PlayerOne and PlayerTwo informing them of the move taken
	...
	7. Once a winning state has been achieved, the game stops and a message is sent to PlayerOne and PlayerTwo
	informing them of which player won.
	8. PlayerOne and PlayerTwo then disconnect (in Client code), and the game state is set to offline (Playing=false)

	If at any point an error is found, the Error message is sent, and the two clients will disconnect. The game will
	terminate semi-normally - it will not immediately kill the server, but will set Playing=false, and wait for deletion.

	Sending the move to both clients fulfils the InformMove condition of the players
	*/

	// Whose turn it is
	unsigned int CurrentPlayer=0;

	// Prestep
	std::stringstream Stream;
	std::string Buffer;
	Stream<<CellContents::Nought;
	Stream>>Buffer;
	Stream.clear();
	Buffer.clear();
	if(!Players[0]->Send(Buffer)) // First player to connect goes first (remote player has symbol sent)
	{
		Players[1]->Send(Error);
		Playing=false;
		return;
	}
	Stream<<CellContents::Cross;
	Stream>>Buffer;
	if(!Players[1]->Send(Buffer)) // Second player to connect goes second (remote player has symbol sent)
	{
		Players[0]->Send(Error);
		Playing=false;
		return;
	}

	// While the game has not been won and the board is not full
	unsigned int CellsFilled=0;
	while((!Board.IsGoalState(CellContents::Cross) && !Board.IsGoalState(CellContents::Nought)) && CellsFilled!=GridSize*GridSize)
	{
		std::string BoardState;
		if(!Players[CurrentPlayer]->Receive(&BoardState))
		{
			Players[CurrentPlayer==0?1:0]->Send(Error);
			Playing=false;
			return;
		}
		// Copy the board
		Grid OldBoard=Board;

		// Parse the new board state, updating the server's version of the board
		if(!Grid::Parse(&BoardState, &Board))
		{
			// Failed to parse new board state - send the error message
			for(unsigned int x=0; x<Players.size(); x++)
			{
				Players[x]->Send(Error);
			}
			Playing=false;
			return;
		}

		// Isolate the move from the grid
		Move NewMove;
		for(unsigned int y=0; y<GridSize; y++)
		{
			for(unsigned int x=0; x<GridSize; x++)
			{
				if(Board.Board[y][x]!=OldBoard.Board[y][x])
				{
					// Mismatch detected
					NewMove.Position=Vector(x, y);
					NewMove.Value=Board.Board[y][x].Get();
				}
			}
		}
		// Convert the move to a string
		std::string SendableMove;
		Move::GetString(&NewMove, &SendableMove);

		// Inform the other player of the move
		if(!Players[CurrentPlayer==0?1:0]->Send(SendableMove))
		{
			Players[CurrentPlayer==0?1:0]->Send(Error);
			Playing=false;
			return;
		}

		// Swap players
		CurrentPlayer==0?CurrentPlayer=1:CurrentPlayer=0;
	}

	// The game has now been won or drawn - each player also has the final board state stored locally, so they can
	// work out who won too.
	// There's nothing left to do but end the game
	Playing=false;
}

bool Game::IsPlaying()
{
	return Playing;
}