#include "Game.h"

#include "ConsoleControl.h"

#include "Windows\PlayerChoiceWindow.h"

Game::Game()
{

}

bool Game::Play()
{
	// Start up by getting the player types for this game
	PlayerChoiceWindow PlayerChoice;
	// Run the window
	if(!PlayerChoice.Run())
	{
		// They exited
		return false;
	}
	// Store the players
	Players.resize(2);
	Players[0]=PlayerChoice.PlayerOne;
	Players[1]=PlayerChoice.PlayerTwo;
	// If we have an online player, we need to configure it
	if(Players[1]->PlayerSymbol==PlayerType::Online)
	{

	}

	// Next stage - initialise the players
	for(unsigned int x=0; x<Players.size(); x++)
	{
		Players[x]->Initialise();
	}

	// Now start the game


	return true;
}