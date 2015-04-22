//
// Created by ssi on 19.04.15.
//

#ifndef TEMPLATESTACK_JSONARRAYSTRUCT_H
#define TEMPLATESTACK_JSONARRAYSTRUCT_H
#include <stddef.h>
#include <iostream>

struct JsonArray
{
	size_t start;
	size_t end;
	size_t curent;
	size_t lastState;
	char openChar;
	std::string jsonArrayString;
};
#endif //TEMPLATESTACK_JSONARRAYSTRUCT_H
