#ifndef _WINDOW_H
#define _WINDOW_H

enum UpdateResult
{
	urEscape,
	urEnter,
	urContinue,
};

class Window
{
public:
	virtual bool Run();

protected:
	virtual UpdateResult Update()=0;
	virtual void Draw(bool Initial=false)=0;
};

#endif