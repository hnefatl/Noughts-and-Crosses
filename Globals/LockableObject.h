#ifndef _LOCKABLEOBJECT_H
#define _LOCKABLEOBJECT_H

#include <mutex>

template <typename T>
class LockableObject
	: public T
{
public:
	void Lock();
	void Unlock();

protected:
	std::mutex ObjectLock;
};

#endif