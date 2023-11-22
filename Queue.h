#pragma once
#include "CriticalSection.h"
#include <vector>

template <class T>
class Queue
{
public:
	Queue(){
		cs = CriticalSection();
		data = std::vector <T>();
	}
	~Queue() {}

	void Push(T val) {
		cs.EnterCriticalSection();
		data.push_back(val);
		cs.LeaveCriticalSection();
	}
	T Pop() {
		cs.EnterCriticalSection();
		T temp = nullptr;
		if (!data.empty())
		{
			temp = data.at(0); 
			data.erase(data.begin());
		}
		cs.LeaveCriticalSection();
		return temp;
	}
	bool empty() { return data.empty(); }
private:
	CriticalSection cs;
	std::vector <T> data;
};

