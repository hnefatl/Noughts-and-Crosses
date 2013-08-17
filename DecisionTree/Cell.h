#ifndef _CELL_H
#define _CELL_H

#include "CellContents.h"

class Cell
{
public:
	Cell();
	Cell(CellContents Contents);

	void Set(CellContents Contents);
	CellContents Get();

	bool operator== (const Cell One) const;
	bool operator!= (const Cell One) const;
private:
	CellContents Contents;
};

#endif