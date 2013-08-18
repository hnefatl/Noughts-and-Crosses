#ifndef _GRID_H
#define _GRID_H

#include "Cell.h"

#include <vector>
#include <string>

class Grid
{
public:
	Grid();

	std::vector<std::vector<Cell>> Board;

	bool IsGoalState(CellContents CurrentPlayer);

	void CalculateGoalStates();

	static bool Parse(std::string *Board, Grid *Buffer);
	static bool GetString(Grid *Board, std::string *Buffer);

	void operator= (const Grid &One);
	bool operator== (const Grid &One) const;
	bool operator!= (const Grid &One) const;
private:
	static void CalculateAllGoalStates(CellContents Player);

	bool NoughtGoalState;
	bool CrossGoalState;

	static std::vector<Grid> NoughtGoalStates;
	static std::vector<Grid> CrossGoalStates;
};

#endif