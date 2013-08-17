#ifndef _TREE_H
#define _TREE_H

#include "Node.h"

class Tree
{
public:
	Tree();

	void Initialise(CellContents AIPlayer);

	int GenerateTree(Node *Current, CellContents CurrentPlayer, CellContents AIPlayer);

	unsigned int GetNodeCount();

private:
	Node *Root;
	unsigned int NodeCount;
};

#endif