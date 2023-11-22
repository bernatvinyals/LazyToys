#pragma once
class SharedMemory
{
public:
	SharedMemory(const char* _name,int _size ,bool _open = false);
	~SharedMemory(void);

	//--

	char* GetPointer(void);
	int Lenght(void);
	char& operator[](int);

private:
	void* handle;
	char* Data;
	int Size;
};

