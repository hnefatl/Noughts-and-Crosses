#include "Move.h"

#include "Util.h"
#include "Globals.h"
#include <vector>
#include <string>
#include <sstream>

Move::Move()
	:Value(CellContents::Empty)
{

}
Move::Move(Vector Position, CellContents Value)
	:Position(Position),
	Value(Value)
{

}

bool Move::Parse(std::string *From, Move *To)
{
	std::vector<std::string> Segments=Split(*From, ':');
	if(Segments.size()!=3)
	{
		return false;
	}

	// Run the conversions
	Move *ChosenMove=new Move();
	try
	{
		std::stringstream Stream;
		Stream<<Segments[0];
		Stream>>ChosenMove->Position.X;
		Stream.clear();
		Stream<<Segments[1];
		Stream>>ChosenMove->Position.Y;
		Stream.clear();
		int Temp;
		Stream<<Segments[2];
		Stream>>Temp;
		ChosenMove->Value=(CellContents)Temp;
	}
	catch(...)
	{
		return false;
	}

	// Store our result
	To=ChosenMove;
	return true;
}
bool Move::GetString(Move *From, std::string *To)
{
	(*To)+=(char)((int)From->Position.X);
	(*To)+=':';
	(*To)+=(char)((int)From->Position.Y);
	(*To)+=':';
	(*To)+=(char)((int)From->Value);

	return true;
}