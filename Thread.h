#pragma once
#include "Definitions.h"
typedef void(*ThreadFunc)(VOIDP);
class ThreadData {
public:
	ThreadFunc pFunc;
	VOIDP pParams;
};
class Thread
{

public:
	Thread(ThreadFunc func);
	Thread(ThreadFunc func, VOIDP params);
	~Thread();

	void Join();
	bool Join(UINT32 time);
	UINT32 GetSystemID();

private:
	UINT32 dwId;
	VOIDP hThread;

};