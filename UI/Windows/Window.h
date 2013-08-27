#ifndef _WINDOW_H
#define _WINDOW_H

class Window
{
public:
	virtual void Run()=0;

protected:
	virtual void Update()=0;
	virtual void Draw()=0;
};

#endif