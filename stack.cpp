//
// Created by ssi on 21.03.15.
//

//#include <glob.h>
#include "stack.h"
#include "renderexception.h"

Stack::Stack(int const *_a, size_t const &_n)
{
	if (_a == nullptr || !_n)
	{
		a = nullptr;
		n = 0;
	}
	else
	{
		n = _n;
		for (int i = 0; i < n; ++i)
		{
			a[i] = _a[i];
		}
	}
}

Stack::Stack(int const &_a)
{
	n = 1;
	a = new int;
	a[0] = _a;
}

Stack::Stack(const Stack &_stack)
{
	if (n > 1)
		delete[] a;
	else
		delete a;
	n = _stack.n;
	a = new int[n];
	for (int i = 0; i < n; ++i)
	{
		a[i] = _stack.a[i];
	}

}

Stack::~Stack()
{
	if (n)
	{
		if (n > 1)
			delete[] a;
		else
			delete a;
	}
}

void Stack::push(const int &_a)
{
	if (n)
	{
		int *temp = new int[n];
		for (int i = 0; i < n; ++i)
		{
			temp[i] = a[i];
		}
		if (n > 1)
			delete[] a;
		else
			delete a;
		++n;
		a = new int[n];
		for (int i = 0; i < n - 1; ++i)
		{
			a[i] = temp[i];
		}
		a[n - 1] = _a;
		if (n > 1)
			delete[] temp;
		else
			delete temp;
	}
	else
	{
		++n;
		a = new int;
		a[0] = _a;
	}
}

int Stack::pop()
{
	if (n)
	{
		int top = a[n - 1];
		--n;
		if (n)
		{
			int *temp = new int[n];
			for (int i = 0; i < n; ++i)
			{
				temp[i] = a[i];
			}
			if (n > 1)
				delete[] a;
			else
				delete a;
			a = new int[n];
			for (int i = 0; i < n; ++i)
			{
				a[i] = temp[i];
			}
			if (n > 1)
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
	else
	{
		throw LOG_TRACE("Stack is empty")
	}
}

void Stack::incTop()
{
	if (n)
		++a[n - 1];
	else
	{
		throw LOG_TRACE("Stack is empty")
	}
}

void Stack::decTop()
{
	if (n)
		--a[n - 1];
	else
	{
		throw LOG_TRACE("Stack is empty")
	}
}

size_t Stack::getCount() const
{
	return n;
}
