#include "GameWindow.h"

#include <iostream>
#include <conio.h>
#include <thread>

#include "..\ConsoleControl.h"

GameWindow::GameWindow(std::vector<Player *> Players)
	:CurrentPlayer(FirstPlayer),
	Board(new Grid()),
	LatestMove(NULL)
{
	this->Players=Players;
}

bool GameWindow::Run()
{	
	// Find the current (first) player
	for(unsigned int x=0; x<Players.size(); x++)
	{
		if(Players[x]->PlayerSymbol==(CellContents)FirstPlayer)
		{
			CurrentPlayer=x;
			break;
		}
	}

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

	// Show the winning screen
	if(Result==UpdateResult::urEnter)
	{
		// Sleep for two seconds to let the player see the final board
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		// Clear the screen and display the win message
		DisplayWin();
	}

	// If the last keypress was Enter, return true. Otherwise, return false.
	return Result==UpdateResult::urEnter;
}

UpdateResult GameWindow::Update()
{
	std::string Result;
	// Let the current player choose the move
	Move *ChosenMove=new Move();

	// Manually update a human player
	if(Players[CurrentPlayer]->Type==PlayerType::Human)
	{
		int KeyPressed;
		Vector LastPosition=Vector(GridSize/2, GridSize/2);
		Vector Position=LastPosition;
		// While not chosen
		while(ChosenMove->Value==CellContents::Empty)
		{
			// Draw
			// Remove previous cursor
			SetCursor(LastPosition.X, LastPosition.Y);
			if(Board->Board[LastPosition.Y][LastPosition.X].Get()==CellContents::Cross)
			{
				SetColour(RED, GREY);
				std::cout<<"X";
			}
			else if(Board->Board[LastPosition.Y][LastPosition.X].Get()==CellContents::Nought)
			{
				SetColour(GREEN, GREY);
				std::cout<<"O";
			}
			else
			{
				SetColour(GREY, GREY);
				std::cout<<"_";
			}
			// Draw new cursor
			SetCursor(Position.X, Position.Y);
			if(Players[CurrentPlayer]->PlayerSymbol==CellContents::Cross)
			{
				// Collision checking
				if(Board->Board[Position.Y][Position.X].Get()!=CellContents::Empty)
				{
					SetColour(RED, RED);
					std::cout<<"_";
				}
				else
				{
					SetColour(RED, GREY);
					std::cout<<"X";
				}
			}
			else
			{
				// Collision checking
				if(Board->Board[Position.Y][Position.X].Get()!=CellContents::Empty)
				{
					SetColour(RED, RED);
					std::cout<<"_";
				}
				else
				{
					SetColour(GREEN, GREY);
					std::cout<<"O";
				}
			}
			// Update
			// Switch positions
			LastPosition=Position;
			KeyPressed=_getch();
			switch (KeyPressed)
			{
			case 13: // Enter key
				// Fill out the move data
				if(Board->Board[Position.Y][Position.X].Get()==CellContents::Empty)
				{
					ChosenMove->Position=Position;
					ChosenMove->Value=Players[CurrentPlayer]->PlayerSymbol;
				}
				break;
			case 224: // Special key
				KeyPressed=_getch();
				switch (KeyPressed)
				{
				case 72: // Up arrow
					if(Position.Y>0)
						Position.Y--;
					break;
				case 80: // Down arrow
					if(Position.Y<GridSize-1)
						Position.Y++;
					break;
				case 75: // Left arrow
					if(Position.X>0)
						Position.X--;
					break;
				case 77: // Right arrow
					if(Position.X<GridSize-1)
						Position.X++;
					break;
				}
			}
		}
	}
	// Automatically update non-human players
	else
	{
		Result=Players[CurrentPlayer]->GetMove(ChosenMove);
		if(Result!="")
		{
			PrintError(Result);
			return UpdateResult::urEscape;
		}
	}
	// Apply the move
	Board->Board[ChosenMove->Position.Y][ChosenMove->Position.X].Set(ChosenMove->Value);
	Board->CalculateGoalStates();
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

	bool Full=true;
	for(unsigned int y=0; y<GridSize; y++)
	{
		for(unsigned int x=0; x<GridSize; x++)
		{
			if(Board->Board[y][x].Get()==CellContents::Empty)
			{
				Full=false;
				break;
			}
		}
		if(!Full)
		{
			break;
		}
	}

	if(Board->IsGoalState(CellContents::Cross) || Board->IsGoalState(CellContents::Nought) || Full)
	{
		// Signal a win
		return UpdateResult::urEnter;
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

	SetColour(GREY, BLACK);
}

void GameWindow::PrintError(std::string Error, std::string Additional)
{
	Clear();
	SetColour(GREY, BLACK);
	std::cout<<"An error occurred."<<std::endl;
	if(Additional!="")
	{
		std::cout<<Additional<<std::endl;
	}
	std::cout<<"The error message is \""<<Error<<"\"."<<std::endl;
	std::cout<<"Press any key to exit...";
	_getch();
}
void GameWindow::DisplayWin()
{
	SetColour(GREY, BLACK);
	Clear();
	if(Board->IsGoalState(CellContents::Cross))
	{
		std::cout<<"Player ";
		SetColour(RED, BLACK);
		std::cout<<"X";
		SetColour(GREY, BLACK);
		std::cout<<" has won!";
	}
	else if(Board->IsGoalState(CellContents::Nought))
	{
		std::cout<<"Player ";
		SetColour(GREEN, BLACK);
		std::cout<<"O";
		SetColour(GREY, BLACK);
		std::cout<<" has won!";
	}
	else
	{
		SetColour(GREY, BLACK);
		std::cout<<"The game resulted in a draw.";
	}
	std::cout<<std::endl<<"Press any key to exit...";
	_getch();
}