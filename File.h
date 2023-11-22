#pragma once
#include <fstream>
#include <iostream>
#include <string>
enum FileAction
{
	Read,Write,Append,Binnary
};

/* 
* 1- Create
* 2- Read
* 3- Use Get Buffer
* 4- Modify contents of buffer
* 5- Write
* 6- Flush
*/
class File
{
	int size;
	std::fstream stream;
	bool isBinary;
	bool failedToOpen;
	char* buffer;
	std::string textBuffer;
public:

	File();
	~File();
	File(File&&) = default;
	File(File&) = default;

	//Define handle and open file
	File(const char* _dir, std::ios_base::openmode _action);

	char* GetBinaryBuffer();
	std::string* GetTextBuffer();

	int Read();
	int Write(const char* _dir = "", bool _binary = false, int _size = 0);
	int Write(char* _buffer, int _size = 0, bool _binary = false, const char* _dir = "");
	void Flush();
};

