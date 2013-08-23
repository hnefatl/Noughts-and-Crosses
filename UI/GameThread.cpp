#include "GameThread.h"

#include "Globals.h"
#include "StatusMessages.h"

GameThread::GameThread(Player *PlayerOne, Player *PlayerTwo, QObject *Parent)
	:QThread(Parent)
{
	Players.resize(2);
	Players[0]=PlayerOne;
	Players[1]=PlayerTwo;
}

void GameThread::run()
{
	if(Players.size()!=2)
	{
		return;
	}

	Players[0]->Initialise();
	if(Players[1]->Type==PlayerType::Online)
	{
		emit SetStatusText(StatusMessages::Net::WaitingForOpponent);
	}
	if(Players[1]->Initialise()!="")
	{
		emit SetStatusText(StatusMessages::Net::OpponentFailedToConnect);
		return;
	}

	unsigned int CurrentPlayer=0;
	unsigned int CellsFilled=0;
	// While not won and the board is not full
	while((!Board.IsGoalState(CellContents::Cross) || !Board.IsGoalState(CellContents::Nought)) && CellsFilled!=GridSize*GridSize)
	{
		if(CurrentPlayer==0)
		{
			emit SetStatusText(StatusMessages::Generic::Player1Turn);
		}
		else
		{
			emit SetStatusText(StatusMessages::Generic::Player2Turn);
		}

		// If we are waiting for a human move, enable the buttons
		if(Players[CurrentPlayer]->Type==PlayerType::Human)
		{
			// Enable buttons that haven't been chosen yet
			emit SetPressableButtonsEnabled(true);
		}
		Move ChosenMove;
		// Non-human player
		if(Players[CurrentPlayer]->Type!=PlayerType::Human)
		{
			// If something went wrong
			if(Players[CurrentPlayer]->GetMove(&ChosenMove)!="")
			{
				emit SetStatusText("Error");
				return;
			}
		}
		else
		{
			// Human player
			// Wait for a button to be pressed
			
			Vector ButtonLocation;
			// TODO: ButtonLocation=emit WaitForButtonPress;

			// Store the necessary data in ChosenMove
			ChosenMove.Position=ButtonLocation;
			ChosenMove.Value=Players[CurrentPlayer]->PlayerSymbol;
		}

		// Set new "virtual" value
		Board.Board[ChosenMove.Position.Y][ChosenMove.Position.X].Set(ChosenMove.Value);
		CellsFilled++;
		// Set new "physical" value
		emit SetButtonEnabled(ChosenMove.Position, false);
		emit SetButtonText(ChosenMove.Position, QString(ChosenMove.Value==CellContents::Cross?"X":"O"));

		// Inform all players of the new state
		for(unsigned int x=0; x<Players.size(); x++)
		{
			Players[x]->InformMove(&Board);
		}

		// Disable the buttons if the player was human
		if(Players[CurrentPlayer]->Type==PlayerType::Human)
		{
			for(unsigned int y=0; y<GridSize; y++)
			{
				for(unsigned int x=0; x<GridSize; x++)
				{
					// Disable the button
					emit SetButtonEnabled(Vector(x, y), false);
				}
			}
		}
		// Swap player
		CurrentPlayer==0?CurrentPlayer=1:CurrentPlayer=0;
	}

	// Game is over
	if(Board.IsGoalState(Players[0]->PlayerSymbol))
	{
		emit SetStatusText(StatusMessages::Generic::Player1Win);
	}
	else if(Board.IsGoalState(Players[1]->PlayerSymbol))
	{
		emit SetStatusText(StatusMessages::Generic::Player2Win);
	}
	else
	{
		emit SetStatusText(StatusMessages::Generic::Draw);
	}
}