#include "Grid.h"

#include "Globals.h"

Grid::Grid()
	:CrossGoalState(false),
	NoughtGoalState(false)
{
	Board.resize(GridSize);
	for(unsigned int x=0; x<GridSize; x++)
	{
		Board[x].resize(GridSize);
	}
}

bool Grid::IsGoalState(CellContents CurrentPlayer)
{
	if(CurrentPlayer==CellContents::Cross)
	{
		return CrossGoalState;
	}
	else
	{
		return NoughtGoalState;
	}
}

void Grid::CalculateGoalStates()
{
	// Goal states haven't been calculated
	if(!(CrossGoalStates.size()>0))
	{
		CalculateAllGoalStates(CellContents::Cross);
	}
	// Run checks for matching goal state
	for(unsigned int z=0; z<CrossGoalStates.size(); z++)
	{
		unsigned int Matches=0;
		for(unsigned int y=0; y<GridSize; y++)
		{
			for(unsigned int x=0; x<GridSize; x++)
			{
				// If the current position is a required match
				if(CrossGoalStates[z].Board[y][x]!=CellContents::Empty)
				{
					// If a required position is matched
					if(CrossGoalStates[z].Board[y][x]==this->Board[y][x])
					{
						// Increase the number of successful matches
						Matches++;
					}
				}
			}
			// If all the required positions match
			if(Matches==WinLength)
			{
				// This is a goal state for Cross
				CrossGoalState=true;
				break;
			}
		}
	}

	if(!(NoughtGoalStates.size()>0))
	{
		CalculateAllGoalStates(CellContents::Nought);
	}
	// Run checks for matching goal state
	for(unsigned int z=0; z<NoughtGoalStates.size(); z++)
	{
		unsigned int Matches=0;
		for(unsigned int y=0; y<GridSize; y++)
		{
			for(unsigned int x=0; x<GridSize; x++)
			{
				// If the current position is a required match
				if(NoughtGoalStates[z].Board[y][x]!=CellContents::Empty)
				{
					// If a required position is matched
					if(NoughtGoalStates[z].Board[y][x]==this->Board[y][x])
					{
						// Increase the number of successful matches
						Matches++;
					}
				}
			}
			// If all the required positions match
			if(Matches==WinLength)
			{
				// This is a goal state for Nought
				NoughtGoalState=true;
				break;
			}
		}
	}
}

bool Grid::Parse(std::string *Board, Grid *Buffer)
{
	if(GridSize*GridSize!=Board->size())
	{
		// Invalid length
		return false;
	}

	for(unsigned int y=0; y<GridSize; y++)
	{
		for(unsigned int x=0; x<GridSize; x++)
		{
			char Symbol=(*Board)[(y*GridSize)+x];
			if(Symbol=='X')
			{
				Buffer->Board[y][x].Set(CellContents::Cross);
			}
			else if(Symbol=='O')
			{
				Buffer->Board[y][x].Set(CellContents::Nought);
			}
			else if(Symbol=='_')
			{
				Buffer->Board[y][x].Set(CellContents::Empty);
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}
bool Grid::GetString(Grid *Board, std::string *Buffer)
{
	std::string Local;
	for(unsigned int y=0; y<GridSize; y++)
	{
		for(unsigned int x=0; x<GridSize; x++)
		{
			CellContents Current=Board->Board[y][x].Get();
			if(Current==CellContents::Cross)
			{
				Local+='X';
			}
			else if(Current==CellContents::Nought)
			{
				Local+='O';
			}
			else if(Current==CellContents::Empty)
			{
				Local+='_';
			}
			else
			{
				return false;
			}
		}
	}

	// Swap strings
	*Buffer=Local;

	return true;
}

void Grid::operator= (const Grid &One)
{
	this->Board=One.Board;
	this->CrossGoalState=One.CrossGoalState;
	this->NoughtGoalState=One.NoughtGoalState;
}
bool Grid::operator== (const Grid &One) const
{
	for(unsigned int y=0; y<GridSize; y++)
	{
		for(unsigned int x=0; x<GridSize; x++)
		{
			if(Board[y][x]!=One.Board[y][x])
			{
				return false;
			}
		}
	}

	return true;
}
bool Grid::operator!= (const Grid &One) const
{
	return !(*this==One);
}

void Grid::CalculateAllGoalStates(CellContents Player)
{
	// Check rows
	for(unsigned int y=0; y<GridSize; y++)
	{
		for(unsigned int x=0; x<GridSize; x++)
		{
			bool Failed=false;
			Grid Working;
			// Loop through all cells along the path
			for(unsigned int WinIterX=0; WinIterX<WinLength; WinIterX++)
			{
				if(x+WinIterX<GridSize)
				{
					// Valid move, place it
					Working.Board[y][x+WinIterX].Set(Player);
				}
				else
				{
					// Failure - set flag
					Failed=true;
					break;
				}
			}

			if(!Failed)
			{
				// Found a winning state
				if(Player==CellContents::Cross)
				{
					CrossGoalStates.push_back(Working);
				}
				else
				{
					NoughtGoalStates.push_back(Working);
				}
			}
		}
	}

	// Check columns
	for(unsigned int x=0; x<GridSize; x++)
	{
		for(unsigned int y=0; y<GridSize; y++)
		{
			bool Failed=false;
			Grid Working;
			// Loop through all cells along the path
			for(unsigned int WinIterY=0; WinIterY<WinLength; WinIterY++)
			{
				if(y+WinIterY<GridSize)
				{
					// Valid move, place it
					Working.Board[y+WinIterY][x].Set(Player);
				}
				else
				{
					// Failure - set flag
					Failed=true;
					break;
				}
			}

			if(!Failed)
			{
				// Found a winning state
				if(Player==CellContents::Cross)
				{
					CrossGoalStates.push_back(Working);
				}
				else
				{
					NoughtGoalStates.push_back(Working);
				}
			}
		}
	}
	// Check diagonals
	for(unsigned int y=0; y<GridSize; y++)
	{
		for(unsigned int x=0; x<GridSize; x++)
		{
			bool Failed=false;
			Grid Working;
			// Loop through all cells along the path (left-to-right)
			for(unsigned int WinIterX=0, WinIterY=0; WinIterX<WinLength && WinIterY<WinLength; WinIterX++, WinIterY++)
			{
				if(x+WinIterX<GridSize && y+WinIterY<GridSize)
				{
					// Valid move, place it
					Working.Board[y+WinIterY][x+WinIterX].Set(Player);
				}
				else
				{
					// Failure - set flag
					Failed=true;
					break;
				}
			}
			if(!Failed)
			{
				// Found a winning state
				if(Player==CellContents::Cross)
				{
					CrossGoalStates.push_back(Working);
				}
				else
				{
					NoughtGoalStates.push_back(Working);
				}
			}

			// Reset the variables
			Failed=false;
			Working=Grid();
			// Loop through all cells along the path (right-to-left)
			for(unsigned int WinIterX=0, WinIterY=0; WinIterX<WinLength && WinIterY<WinLength; WinIterX++, WinIterY++)
			{
				if((int)x-(int)WinIterX>=0 && y+WinIterY<GridSize)
				{
					// Valid move, place it
					Working.Board[y+WinIterY][x-WinIterX].Set(Player);
				}
				else
				{
					// Failure - set flag
					Failed=true;
					break;
				}
			}
			if(!Failed)
			{
				// Found a winning state
				if(Player==CellContents::Cross)
				{
					CrossGoalStates.push_back(Working);
				}
				else
				{
					NoughtGoalStates.push_back(Working);
				}
			}
		}
	}
}

std::vector<Grid> Grid::NoughtGoalStates;
std::vector<Grid> Grid::CrossGoalStates;