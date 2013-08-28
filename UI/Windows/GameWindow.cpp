#include "GameWindow.h"

#include <iostream>
#include <conio.h>

#include "..\ConsoleControl.h"

GameWindow::GameWindow()
	:CurrentPlayer(FirstPlayer),
	Board(new Grid()),
	LatestMove(NULL)
{

}

bool GameWindow::Run()
{	
	// Disable the cursor
	EnableCursor(false);
	// Inital drawing
	Draw(true);
	// Window loop - update then draw
	UpdateResult Result;
	do
	{
		// Get the result of this "frame"
		Result=Update();
		// Draw any changes
		Draw();
		// Switch player
		CurrentPlayer=(CurrentPlayer==0?1:0);
	} while(Result==UpdateResult::urContinue);

	// If the last keypress was Enter, return true. Otherwise, return false.
	return Result==UpdateResult::urEnter;
}

UpdateResult GameWindow::Update()
{
	std::string Result;
	// Let the current player choose the move
	Move *ChosenMove=new Move();
	Result=Players[CurrentPlayer]->GetMove(ChosenMove);
	if(Result!="")
	{
		PrintError(Result);
		return UpdateResult::urEscape;
	}
	// Apply the move
	Board->Board[ChosenMove->Position.X][ChosenMove->Position.Y].Set(ChosenMove->Value);
	// Store it as the latest move
	// Prevent memory leaks
	if(LatestMove!=NULL)
	{
		delete LatestMove;
	}
	LatestMove=ChosenMove;
	// Inform all players of the move
	for(unsigned int x=0; x<Players.size(); x++)
	{
		Result=Players[x]->InformMove(Board);
		if(Result!="")
		{
			PrintError(Result, "The player being informed was "+x);
			return UpdateResult::urEscape;
		}
	}

	return UpdateResult::urContinue;
}
void GameWindow::Draw(bool Initial)
{
	if(Initial)
	{
		// Draw the grey grid
		Clear();
		SetColour(GREY, GREY);
		for(unsigned int y=0; y<Board->Board.size(); y++)
		{
			for(unsigned int x=0; x<Board->Board[y].size(); x++)
			{
				std::cout<<"_";
			}
			std::cout<<std::endl;
		}
	}
	else
	{
		if(Players[CurrentPlayer]->PlayerSymbol==CellContents::Cross)
		{
			SetColour(RED, GREY);
		}
		else
		{
			SetColour(GREEN, GREY);
		}

		SetCursor(LatestMove->Position.X, LatestMove->Position.Y);
		if(Players[CurrentPlayer]->PlayerSymbol==CellContents::Cross)
		{
			std::cout<<"X";
		}
		else
		{
			std::cout<<"O";
		}
	}
}

void GameWindow::PrintError(std::string Error, std::string Additional)
{
	Clear();
	std::cout<<"An error occurred."<<std::endl;
	if(Additional!="")
	{
		std::cout<<Additional<<std::endl;
	}
	std::cout<<"The error message is \""<<Error<<"\"."<<std::endl;
	std::cout<<"Press any key to exit...";
	_getch();
}