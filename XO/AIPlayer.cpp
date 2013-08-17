#include "AIPlayer.h"

#include "Globals.h"

#include <vector>
#include <ctime>

AIPlayer::AIPlayer()
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
	srand(time(NULL));

	// Return no error
	return "";
}

std::string AIPlayer::GetMove(Move *ChosenMove)
{
	// Find best move (minimax algorithm)
	// Loop through all children
	int BestScore=0;
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

	// Randomly pick a branch frm the best choices
	Node *BestChoice=BestChoices[rand()%BestChoices.size()];
	BestChoices.clear(); // Clear up the list of best choices

	// Derive the move from the choice
	for(unsigned int y=0; y<GridSize; y++)
	{
		for(unsigned int x=0; x<GridSize; x++)
		{
			// Find a change in the states between the current one and the next
			if(Root->State.Board[y][x]!=BestChoice->State.Board[y][x])
			{
				// Set up the chosen move with a position to move to and a value
				ChosenMove=new Move(Vector(x, y), BestChoice->State.Board[y][x].Get());
				return ""; // Return no error
			}
		}
	}

	// Return no error
	return "";
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