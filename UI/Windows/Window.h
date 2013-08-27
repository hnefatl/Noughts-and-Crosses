#ifndef _WINDOW_H
#define _WINDOW_H

enum UpdateResult
{
	Escape,
	Enter,
	Continue,
};

class Window
{
public:
	virtual void Run()=0;

protected:
	virtual UpdateResult Update()=0;
	virtual void Draw(bool Initial=false)=0;
};

#endif