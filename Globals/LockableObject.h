#ifndef _LOCKABLEOBJECT_H
#define _LOCKABLEOBJECT_H

#include <mutex>

template <typename T>
class LockableObject
	: public T
{
public:
	void Lock()
	{
		ObjectLock.lock();
	}
	void Unlock()
	{
		ObjectLock.unlock();
	}

protected:
	std::mutex ObjectLock;
};

#endif