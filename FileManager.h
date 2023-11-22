#pragma once
#include "CriticalSection.h"
#include "Thread.h"
#include <vector>
#include <string>
#include "Queue.h"

class File {
public:
	File(const char* _path);
	bool Read();
	const char* path;
	char* data;
	unsigned long size;
	volatile bool finished;
	CriticalSection cs;
};

class FileManager
{
public: 
	FileManager();
	~FileManager();

	void AddFile(File* _task);
	
	bool IsFinished();
	unsigned int MaxThreads;
	volatile bool SelfDestruct;
	Queue<File*> Tasks;
	Thread* MainThread;
	CriticalSection cs;
};

