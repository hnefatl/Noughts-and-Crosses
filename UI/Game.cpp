#include "Game.h"

#include "ConsoleControl.h"

#include "Windows\PlayerChoiceWindow.h"
#include "Windows\NetworkOptions.h"
#include "Windows\GameWindow.h"

#include <string>
#include <conio.h>

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
		return true;
	}
	// Store the players
	Players.resize(2);
	Players[0]=PlayerChoice.PlayerOne;
	Players[1]=PlayerChoice.PlayerTwo;
	// If we have an online player, we need to configure it
	if(Players[1]->Type==PlayerType::Online)
	{
		// Create and run a new window
		NetworkOptions NetOptions;

		if(!NetOptions.Run())
		{
			// Escaped out
			return true;
		}
		// Cast the Player to an online player
		OnlinePlayer *Online=static_cast<OnlinePlayer *>(Players[1]);
		// Set the players' connection data
		Online->SetData(NetOptions.IP, NetOptions.Port);
	}
	Clear();

	// Next stage - initialise the players
	// Find if there's an OnlinePlayer playing - they need to be updated first
	bool OnlinePlayerPlaying=false;
	for(unsigned int x=0; x<Players.size(); x++)
	{
		// Only update an online player
		if(Players[x]->Type==PlayerType::Online)
		{
			OnlinePlayerPlaying=true;
			std::cout<<"Initialising player "<<(x+1)<<"...";
			// This sets the turn
			std::string Result=Players[x]->Initialise();
			std::cout<<"Done."<<std::endl;
			// If an error occurred
			if(Result!="")
			{
				Clear();
				std::cout<<"An error occurred while initialising player "<<(x+1)<<"."<<std::endl;
				std::cout<<"The error message returned was \""<<Result<<"\"."<<std::endl;
				std::cout<<"Press any key to exit...";
				_getch();
				return false;
			}
		}
	}

	// If there isn't an online player
	if(!OnlinePlayerPlaying)
	{
		// Assign symbols locally
		Players[0]->PlayerSymbol=CellContents::Cross;
		Players[1]->PlayerSymbol=CellContents::Nought;
	}
	else
	{
		// Online players symbol will have already been received+set
		// Set the offline players symbol to the opposite of the online players symbol
		Players[0]->PlayerSymbol=(Players[1]->PlayerSymbol==CellContents::Cross?CellContents::Nought:CellContents::Cross);
	}

	for(unsigned int x=0; x<Players.size(); x++)
	{
		// Only update non-online players
		if(Players[x]->Type!=PlayerType::Online)
		{
			std::cout<<"Initialising player "<<(x+1)<<"...";
			std::string Result=Players[x]->Initialise();
			std::cout<<"Done."<<std::endl;
			// If an error occurred
			if(Result!="")
			{
				Clear();
				std::cout<<"An error occurred while initialising player "<<(x+1)<<"."<<std::endl;
				std::cout<<"The error message returned was \""<<Result<<"\"."<<std::endl;
				std::cout<<"Press any key to exit...";
				_getch();
				return false;
			}
		}
	}

	// Now start the game
	GameWindow Game(Players);
	if(!Game.Run())
	{
		return false;
	}

	return true;
}