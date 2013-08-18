#include "Move.h"

Move::Move()
	:Value(CellContents::Empty)
{

}
Move::Move(Vector Position, CellContents Value)
	:Position(Position),
	Value(Value)
{

}