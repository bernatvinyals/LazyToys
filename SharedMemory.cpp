#include "SharedMemory.h"
#include <Windows.h>
SharedMemory::SharedMemory(const char* _name,int _size, bool _open)
{
	handle = INVALID_HANDLE_VALUE;
	Data = nullptr;
	Size = _size;
	if (_open)
	{
		handle = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, _name);
	}
	else
	{
		handle = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, Size, _name);
		
	}
	if (handle == NULL)
	{
		//ERROR
		ExitProcess(0);
	}
	Data = (char*)MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, Size);
	if (Data == NULL)
	{
		ExitProcess(0);
	}
}


SharedMemory::~SharedMemory(void)
{
	UnmapViewOfFile(Data);
	CloseHandle(handle);
}

char* SharedMemory::GetPointer(void)
{
	return Data;
}

int SharedMemory::Lenght(void)
{
	return Size;
}

char& SharedMemory::operator[](int i)
{
	// TODO: insert return statement here
	if (i >= Size)
	{
		//Exit
		ExitProcess(0);
	}
	return Data[i];
}
