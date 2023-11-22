#include "Mutex.h"
#include <Windows.h>
Mutex::Mutex()
{
	hMutex = CreateMutexA(NULL, FALSE, NULL);
}

Mutex::Mutex(const char* name)
{
	hMutex = CreateMutexA(NULL, FALSE, name);
}

Mutex::Mutex(bool owned)
{
	hMutex = CreateMutexA(NULL, owned, NULL);
}

Mutex::Mutex(bool owned, const char* name)
{
	hMutex = CreateMutexA(NULL, owned, name);
}

Mutex::~Mutex()
{
	CloseHandle(hMutex);
}

void Mutex::Lock()
{
	DWORD dwResult = WaitForSingleObject(hMutex, INFINITE);
	if (dwResult != WAIT_OBJECT_0)
	{
		ExitProcess(0);
	}
}

bool Mutex::TryLock(UINT32 time)
{
	DWORD dwResult = WaitForSingleObject(hMutex, time);
	if (dwResult != WAIT_OBJECT_0)
	{
		return true;
	}
	else if (dwResult != WAIT_TIMEOUT)
	{
		return false;
	}
	else 
	{
		ExitProcess(0);
		return false;
	}
}

void Mutex::Unlock()
{
	ReleaseMutex(hMutex);
}
