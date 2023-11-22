#pragma once
#include <Windows.h>

class CriticalSection
{
	volatile SHORT check;
public:
	CriticalSection();
	~CriticalSection();
	void EnterCriticalSection();
	void LeaveCriticalSection();
};

