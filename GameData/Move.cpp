#include "Move.h"

#include "Util.h"

Move::Move()
	:Value(CellContents::Empty)
{

}
Move::Move(Vector Position, CellContents Value)
	:Position(Position),
	Value(Value)
{

}

bool Parse(std::string *From, Move *To)
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
	ChosenMove->Position.X=atoi(Segments[0].c_str());
	ChosenMove->Position.Y=atoi(Segments[1].c_str());
	ChosenMove->Value=(CellContents)atoi(Segments[2].c_str());
	}
	catch(...)
	{
		return false;
	}
	
	// Store our result
	To=ChosenMove;
	return true;
}
bool GetString(Move *From, std::string *To)
{
	(*To)+=From->Position.X;
	(*To)+=':';
	(*To)+=From->Position.Y;
	(*To)+=':';
	(*To)+=(char)From->Value;

	return true;
}