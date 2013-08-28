#include "Windows\Window.h"

bool Window::Run()
{
	// Inital drawing
	Draw(true);
	// Window loop - update then draw
	UpdateResult Result;
	do
	{
		// Get the result of this "frame"
		Result=Update();
		// Draw any changes
		Draw();
	} while(Result==UpdateResult::urContinue);

	// If the last keypress was Enter, return true. Otherwise, return false.
	return Result==UpdateResult::urEnter;
}