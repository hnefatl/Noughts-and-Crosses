#include "Node.h"

Node::Node()
	:Parent(NULL),
	Score(0)
{
}
Node::~Node()
{
	// Clean up all children (who'll clean up their children etc.)
	for(unsigned int x=0; x<Children.size(); x++)
	{
		delete Children[x];
		Children[x]=NULL;
	}
}

bool Node::HasParent()
{
	return Parent!=NULL;
}
bool Node::HasChildren()
{
	return Children.size()>0;
}

void Node::SetParent(Node *Parent)
{
	this->Parent=Parent;
}
void Node::AddChild(Node *Child)
{
	Children.push_back(Child);
}

Node *Node::GetParent()
{
	return Parent;
}
std::vector<Node *> Node::GetChildren()
{
	return Children;
}

Node *Node::CloneBranch()
{
	// Create clone of this node
	Node *Current=new Node();
	Current->State=this->State;
	Current->Score=this->Score;

	// Clone each child (if there are any)
	for(unsigned int x=0; x<Children.size(); x++)
	{
		Current->AddChild(Children[x]->CloneBranch());
	}

	return Current;
}