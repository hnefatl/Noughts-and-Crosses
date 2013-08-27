#ifndef _PLAYERCHOICEWINDOW_H
#define _PLAYERCHOICEWINDOW_H

#include "Window.h"

class PlayerChoiceWindow
	: public Window
{
public:
	virtual void Run();

protected:
	virtual void Update();
	virtual void Draw();
};

#endif