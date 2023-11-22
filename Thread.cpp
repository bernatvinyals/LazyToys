#include "Thread.h"
#include <Windows.h>

DWORD _stdcall DefaultThreadFunc(LPVOID params) {
	ThreadData* data = (ThreadData*)params;
	data->pFunc(data->pParams);
	delete data;
	return 0;
}

Thread::Thread(ThreadFunc func)
{
	DWORD dwSysId = 0;
	ThreadData* data = new ThreadData();
	data->pFunc = func;
	data->pParams = 0;
	hThread = CreateThread(NULL, 0, DefaultThreadFunc, data, 0, &dwSysId);
	dwId = dwSysId;
}

Thread::Thread(ThreadFunc func, VOIDP params)
{
	DWORD dwSysId = 0;
	ThreadData* data = new ThreadData();
	data->pFunc = func;
	data->pParams = params;
	hThread = CreateThread(NULL, 0, DefaultThreadFunc, data, 0, &dwSysId);
	dwId = dwSysId;
}
Thread::~Thread()
{
	CloseHandle(hThread);
}

void Thread::Join()
{
	DWORD dwResult = WaitForSingleObject(hThread, INFINITE);
	if (dwResult != WAIT_OBJECT_0)
	{
		ExitProcess(0);
	}
}

bool Thread::Join(UINT32 time)
{
	DWORD dwResult = WaitForSingleObject(hThread, time);
	if (dwResult == WAIT_OBJECT_0)
	{
		return true;
	}
	else if (dwResult == WAIT_TIMEOUT)
	{
		return false;
	}
	else
	{
		ExitProcess(0);
		return false;
	}
}

UINT32 Thread::GetSystemID()
{
	return dwId;
}
