#include "AIPlayer.h"

#include "Globals.h"

#include <vector>
#include <ctime>
#include <iostream>

AIPlayer::AIPlayer()
	:Player(PlayerType::AI)
{

}
AIPlayer::~AIPlayer()
{
	delete Root;
	Root=NULL;
}

std::string AIPlayer::Initialise()
{
	// Seed the random generator
	srand((unsigned int)time(NULL));

	// Initialise the root node (with a blank board)
	Root=new Node();
	Root->State=Grid();

	// Generate the decision tree
	GenerateTree(Root, (CellContents)FirstPlayer);

	// Return no error
	return "";
}

std::string AIPlayer::GetMove(Move *ChosenMove)
{
	// Find best move (minimax algorithm)
	// Loop through all children
	int BestScore=Root->GetChildren()[0]->Score;
	std::vector<Node *> BestChoices;
	for(unsigned int x=0; x<Root->GetChildren().size(); x++)
	{
		// If a better score has been found
		if(Root->GetChildren()[x]->Score>BestScore)
		{
			// Store the best score
			BestScore=Root->GetChildren()[x]->Score;
			// Empty the list of best choices
			BestChoices.clear();
			// Add the new best choice to the list
			BestChoices.push_back(Root->GetChildren()[x]);
		}
		// If a branch with the same score has been found
		else if(Root->GetChildren()[x]->Score==BestScore)
		{
			// Store this branch another best choice
			BestChoices.push_back(Root->GetChildren()[x]);
		}
	}
	// Randomly pick a branch from the best choices
	Node *BestChoice=BestChoices[rand()%BestChoices.size()];
	// Derive the move from the choice
	for(unsigned int y=0; y<GridSize; y++)
	{
		for(unsigned int x=0; x<GridSize; x++)
		{
			// Find a change in the states between the current one and the next
			if(Root->State.Board[y][x]!=BestChoice->State.Board[y][x])
			{
				// Set up the chosen move with a position to move to and a value
				*ChosenMove=Move(Vector(x, y), BestChoice->State.Board[y][x].Get());
				return ""; // Return no error
			}
		}
	}

	// Return no error
	return "No move was chosen.";
}

std::string AIPlayer::InformMove(Grid *NewState)
{
	// Remount the tree with the next state as root
	// Loop through all children and find a match
	Node *NewRoot=NULL;
	for(unsigned int x=0; x<Root->GetChildren().size(); x++)
	{
		// Check for match
		if(Root->GetChildren()[x]->State==*NewState)
		{
			NewRoot=Root->GetChildren()[x];
		}
	}
	if(NewRoot==NULL)
	{
		return "Informed of move that is impossible to make from current position.";
	}

	// Remount the tree
	Node *NewTree=NewRoot->CloneBranch();
	delete Root;
	Root=NewTree;

	// Return no error
	return "";
}

void AIPlayer::GenerateTree(Node *Current, CellContents CurrentPlayer)
{
	// If child nodes need to be generated - if this node is not a goal node
	if(!(Current->State.IsGoalState(CellContents::Cross) || Current->State.IsGoalState(CellContents::Nought)))
	{
		// Generate all possible child states
		for(unsigned int y=0; y<GridSize; y++)
		{
			for(unsigned int x=0; x<GridSize; x++)
			{
				// If a move could be placed here
				if(Current->State.Board[y][x].Get()==CellContents::Empty)
				{
					// Create a copy of the current state
					Grid NewBoard=Current->State;
					// Modify it to the new possible state
					NewBoard.Board[y][x].Set(CurrentPlayer);
					// Set up the goal states for the board
					NewBoard.CalculateGoalStates();

					// Create a new child node
					Node *NewChild=new Node();
					// Set the parent
					NewChild->SetParent(Current);
					// Set the state
					NewChild->State=NewBoard;
					// Add the new node as a child
					Current->AddChild(NewChild);
					// Generate the states from that state, switching the current player
					GenerateTree(NewChild, CurrentPlayer==CellContents::Cross?CellContents::Nought:CellContents::Cross);
				}
			}
		}
	}

	// Calculate this node's score
	if(Current->HasChildren())
	{
		// Maximise the value
		if(CurrentPlayer==FirstPlayer)
		{
			int HighestScore=Current->GetChildren()[0]->Score;
			for(unsigned int x=0; x<Current->GetChildren().size(); x++)
			{
				if(Current->GetChildren()[x]->Score>HighestScore)
				{
					HighestScore=Current->GetChildren()[x]->Score;
				}
			}
			Current->Score=HighestScore;
		}
		// Minimise the value
		else
		{
			int LowestScore=Current->GetChildren()[0]->Score;
			for(unsigned int x=0; x<Current->GetChildren().size(); x++)
			{
				if(Current->GetChildren()[x]->Score<LowestScore)
				{
					LowestScore=Current->GetChildren()[x]->Score;
				}
			}
			Current->Score=LowestScore;
		}
	}
	else
	{
		if(Current->State.IsGoalState(CellContents::Cross))
		{
			Current->Score=1;
		}
		else if(Current->State.IsGoalState(CellContents::Nought))
		{
			Current->Score=-1;
		}
		else
		{
			Current->Score=0;
		}
	}

	// Return to calling function, backtracking up the call stack
}