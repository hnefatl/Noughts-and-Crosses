#include "Game.h"

Game::Game()
	:Playing(false)
{
}
Game::Game(Client *PlayerOne, Client *PlayerTwo)
	:Playing(false)
{
	Players.push_back(PlayerOne);
	Players.push_back(PlayerTwo);
}

void Game::Play()
{
	/*
	The structure of the game is thus:
	1. Send a message to PlayerOne informing it that it is its go.
	2. Receive a message from PlayerOne informing the server of the move taken.
	3. Send a message to PlayerOne and PlayerTwo informing them of the move taken
	4. Send a message to PlayerTwo informing it that it is its go
	5. Receive a message from PlayerTwo informing the server of the move taken
	6. Send a message to PlayerOne and PlayerTwo informing them of the move taken

	Sending the move to both clients fulfils the InformMove condition of the players
	*/

	
}

bool Game::IsPlaying()
{
	return Playing;
}