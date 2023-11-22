#pragma once
#include "Definitions.h"
class Mutex
{
public:
	Mutex();
	Mutex(const char* name);
	Mutex(bool owned);
	Mutex(bool owned, const char* name);
	~Mutex();
	void Lock();
	bool TryLock(UINT32 time);
	void Unlock();
private:
	VOIDP hMutex;
	const char* mutexName;
};

