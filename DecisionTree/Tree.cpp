#include "Tree.h"
#include "Globals.h"

Tree::Tree()
	:Root(NULL),
	NodeCount(0)
{
}

void Tree::Initialise()
{
	Root=new Node();
	GenerateTree(Root, (CellContents)FirstPlayer);
}

int Tree::GenerateTree(Node *Current, CellContents CurrentPlayer, CellContents AIPlayer)
{
	// Increase the NodeCount, as this is a new node to be processed
	NodeCount++;

	// Only generate children if this node is not a goal state - otherwise we can start to backtrack immediately
	if(!Current->State.IsGoalState(CurrentPlayer))
	{
		// Loop through each position on the board
		for(unsigned int y=0; y<GridSize; y++)
		{
			for(unsigned int x=0; x<GridSize; x++)
			{
				// If the current cell is empty
				if(Current->State.Board[y][x].Get()==CellContents::Empty)
				{
					// Create a new Node to be a child, and clone the current board
					Node *Child=new Node();
					Child->State=Current->State;
					Child->SetParent(Current);

					// Alter the board to a new state
					Child->State.Board[y][x].Set(CurrentPlayer);
					// Check it for being a goal state
					Child->State.CalculateGoalStates();
					// Store as child
					Current->AddChild(Child);
					// Generate its tree, swapping the player
					Current->Score+=GenerateTree(Child, CurrentPlayer==CellContents::Cross?CellContents::Nought:CellContents::Cross);
				}
			}
		}
	}

	// Generate this Node's score
	// If the AI will choose the move
	if(CurrentPlayer==AIPlayer)
	{
		// If this node is a goal state for the AI
		if(Current->State.IsGoalState(CurrentPlayer))
		{
			// Increase its score
			Current->Score++;
		}
		// If this node is a goal state for the player
		if(Current->State.IsGoalState(CurrentPlayer==CellContents::Cross?CellContents::Nought:CellContents::Cross))
		{
			// Decrease its score
			Current->Score--;
		}
	}
	else // The player will choose the move
	{
		// If this node is a goal state for the player
		if(Current->State.IsGoalState(CurrentPlayer))
		{
			// Decrease its score
			Current->Score--;
		}
		// If this node is a goal state for the AI
		if(Current->State.IsGoalState(CurrentPlayer==CellContents::Cross?CellContents::Nought:CellContents::Cross))
		{
			// Increase its score
			Current->Score++;
		}
	}


	// Return this node's score for use by its parent
	return Current->Score;
}

unsigned int Tree::GetNodeCount()
{
	return NodeCount;
}