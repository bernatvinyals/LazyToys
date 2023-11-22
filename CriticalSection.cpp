#include "CriticalSection.h"

CriticalSection::CriticalSection()
{
	check = 0;
}

CriticalSection::~CriticalSection()
{
}

void CriticalSection::EnterCriticalSection()
{
	while (_InterlockedCompareExchange16(&check, 1, 0))
	{
		Sleep(0);
	}
}

void CriticalSection::LeaveCriticalSection()
{
	_InterlockedDecrement16(&check);
}
