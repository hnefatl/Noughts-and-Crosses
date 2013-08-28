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

protected:
	virtual UpdateResult Update();
	virtual void Draw(bool Initial=false);

	std::string IP, Port;
}

#endif