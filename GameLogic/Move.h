#ifndef _MOVE_H
#define _MOVE_H

#include "Vector.h"
#include "CellContents.h"

class Move
{
public:
	Move();
	Move(Vector Position, CellContents Value);

	Vector Position;
	CellContents Value;
};

#endif