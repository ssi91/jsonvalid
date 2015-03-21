//
// Created by ssi on 21.03.15.
//

#ifndef _JSONVALID_STACK_H_
#define _JSONVALID_STACK_H_


#include <stddef.h>

class Stack
{
private:
	int *a;
	size_t n;
public:
	Stack(const int *_a = nullptr, const size_t &_n = 0);
	Stack(const int &_a);
	Stack(const Stack &_stack);
	~Stack();
	void push(const int &_a);
	int pop();
	void incTop();
	void decTop();
	size_t getCount() const;
};


#endif //_JSONVALID_STACK_H_
