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

}

bool Game::IsPlaying()
{
	return Playing;
}