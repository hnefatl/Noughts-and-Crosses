#include "LockableObject.h"

template <typename T>
void LockableObject<T>::Lock()
{
	ObjectLock.lock();
}

template <typename T>
void LockableObject<T>::Unlock()
{
	ObjectLock.unlock();
}