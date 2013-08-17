#include "Cell.h"

Cell::Cell()
	:Contents(CellContents::Empty)
{

}
Cell::Cell(CellContents Contents)
	:Contents(Contents)
{

}

void Cell::Set(CellContents Contents)
{
	this->Contents=Contents;
}
CellContents Cell::Get()
{
	return this->Contents;
}

bool Cell::operator== (const Cell One) const
{
	return (int)this->Contents==(int)One.Contents;
}
bool Cell::operator!= (const Cell One) const
{
	return !(*this==One);
}