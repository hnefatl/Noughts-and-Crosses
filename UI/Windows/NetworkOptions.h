#ifndef _NETWORKOPTIONS_H
#define _NETWORKOPTIONS_H

#include "Window.h"

#include <string>

class NetworkOptions
	: public Window
{
public:
	NetworkOptions();

	// virtual bool Run();     // Default implementation suffices

	std::string IP, Port;
protected:
	virtual UpdateResult Update();
	virtual void Draw(bool Initial=false);

	bool IsNumber(char Input);
	bool IsDot(char Input);
	bool IsValidInput();

	unsigned int CurrentlySelected;
	std::string OldIP, OldPort;

	std::string IPText, PortText;
};

#endif