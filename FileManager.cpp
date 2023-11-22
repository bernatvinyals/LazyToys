#include "FileManager.h"

void DummyFunction(VOIDP _val) {
	FileManager* TP = (FileManager*)_val;

	while (!TP->IsFinished())
	{
		File* tempFile = nullptr;
		TP->cs.EnterCriticalSection();
		if (TP->Tasks.empty() == false)
		{
			tempFile = TP->Tasks.Pop();
		}
		TP->cs.LeaveCriticalSection();
		if (tempFile != nullptr)
		{
			tempFile->Read();
			tempFile->cs.EnterCriticalSection();
			tempFile->finished = true;
			tempFile->cs.LeaveCriticalSection();
		}
		Sleep(10);
	}
}


FileManager::FileManager()
{
	MainThread = new Thread(DummyFunction, this);
}

FileManager::~FileManager()
{
	SelfDestruct = true;
	MainThread->Join();
	delete MainThread;
}


void FileManager::AddFile(File* _file)
{
	cs.EnterCriticalSection();
	Tasks.Push(_file);
	cs.LeaveCriticalSection();
}

bool FileManager::IsFinished()
{
	bool retured;
	cs.EnterCriticalSection();
	retured = SelfDestruct;
	cs.LeaveCriticalSection();
	return retured;
}


File::File(const char* _path)
{
	path = _path;
	data = nullptr;
	size = 0;
	finished = false;
	cs = CriticalSection();
}

bool File::Read()
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	hFile = CreateFileA(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		DWORD error = GetLastError();
		printf("ERROR: %d\n", error);
		getchar();
		return 0;
	}
	size = GetFileSize(hFile, NULL);
	data = (char*)malloc(size);

	DWORD nBytesRead = 0;
	BOOL bResult = ReadFile(hFile, data, size, &nBytesRead, 0);
	if (bResult != TRUE)
	{
		DWORD error = GetLastError();
		printf("ERROR: %d\n", error);
		return -1;
	}
	CloseHandle(hFile);
	return true;
}
