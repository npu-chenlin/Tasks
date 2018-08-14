#ifndef _STACK_H
#define _STACK_H
#include <iostream>

template <typename T> class stack
{
public:
	stack(int size = 10)
	{
		maxSize = size;
		element = new T[maxSize];
		top = -1;
	}
	~stack()
	{
		delete[] element;
	}

	bool push(T data);
	T pop();
private:
	int maxSize;
	T* element;
	int top;
};

template <typename T> bool stack<T>::push(T data)
{
	if(top == maxSize)return false;
	element[++top] = data;
	return true;
}
template <typename T> T stack<T>::pop()
{
	if(top == -1) return 0;
	return element[top--];
}
#endif
