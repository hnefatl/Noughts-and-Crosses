#ifndef _NODE_H
#define _NODE_H

#include "Grid.h"

#include <vector>

class Node
{
public:
	Node();
	~Node();

	bool HasParent();
	bool HasChildren();

	void SetParent(Node *Parent);
	void AddChild(Node *Child);

	Node *GetParent();
	std::vector<Node *> GetChildren();

	Node *CloneBranch();

public:
	int Score;
	Grid State;

private:

	Node *Parent;
	std::vector <Node *> Children;
};

#endif