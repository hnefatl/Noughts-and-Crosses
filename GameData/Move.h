#ifndef _MOVE_H
#define _MOVE_H

#include "Vector.h"
#include "CellContents.h"

#include <string>

class Move
{
public:
	Move();
	Move(Vector Position, CellContents Value);

	static bool Parse(std::string *From, Move *To);
	static bool GetString(Move *From, std::string *To);

	Vector Position;
	CellContents Value;
};

#endif