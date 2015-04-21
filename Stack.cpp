//
// Created by ssi on 03.04.15.
//

#include "Stack.h"
#include "renderexception.h"

template<class T>
Stack<T>::Stack()
{
	count = 0;
}

template<>
Stack<int>::Stack(const int &_a)
{
	count = 1;
	a = new int;
	a[0] = _a;
}

template<class T>
Stack<T>::~Stack()
{
	if (!getCount())
		return;
	else if (getCount() == 1)
		delete a;
	else
		delete[] a;
}

template<class T>
void Stack<T>::push(T const &_a)
{
	if (count)
	{
		T *temp;
		if (count > 1)
		{
			temp = new T[count];
			for (int i = 0; i < count; ++i)
			{
				temp[i] = a[i];
			}
		}
		else
		{
			temp = new T;
			temp[0] = a[0];
		}
		if (count > 1)
			delete[] a;
		else
			delete a;
		a = new T[count + 1];

		for (int i = 0; i < count; ++i)
		{
			a[i] = temp[i];
		}
		a[count] = _a;
		if (count > 1)
			delete[] temp;
		else
			delete temp;
	}
	else
	{
		a = new T;
		a[0] = _a;
	}
	count++;
}

template<class T>
T Stack<T>::pop()
{
	if (count)
	{
		T top = a[count - 1];
		--count;
		if (count)
		{
			T *temp = new T[count];
			for (int i = 0; i < count; ++i)
			{
				temp[i] = a[i];
			}
//			if (count > 1)
			delete[] a;
//			else
//				delete a;
			a = new T[count];
			for (int i = 0; i < count; ++i)
			{
				a[i] = temp[i];
			}
			if (count > 1)
				delete[] temp;
			else
				delete temp;
		}
		else
		{
			delete a;
		}
		return top;
	}
}

template<>
void Stack<char>::incTop()
{
	if (count)
		++a[count - 1];
	else
	{
		throw LOG_TRACE("Stack is empty")
	}
}

template<>
void Stack<int>::incTop()
{
	if (count)
		++a[count - 1];
	else
	{
		throw LOG_TRACE("Stack is empty")
	}
}

template<>
void Stack<char>::decTop()
{
	if (count)
		--a[count - 1];
	else
	{
		throw LOG_TRACE("Stack is empty")
	}
}

template<>
void Stack<int>::decTop()
{
	if (count)
		--a[count - 1];
	else
	{
		throw LOG_TRACE("Stack is empty")
	}
}

template<class T>
size_t Stack<T>::getCount()
{
	return count;
}

template<class T>
T &Stack<T>::getTop()
{
	if (count)
	{
		return a[count - 1];
	}
}
