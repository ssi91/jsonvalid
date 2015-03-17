//
// Created by ssi on 17.03.15.
//

#include <iostream>
#include <sys/types.h>
#include "fsmjson.h"

FSMJson::FSMJson(const char *_s)
{
	n = 0;
	bool isNull = false;
	if (_s == NULL)
	{
		n = 1;
		s = new char;
		strcpy(s, _s);
	}
	else
	{
		while (_s[n] != '\0')
		{
			n++;
		}
		n++;
		s = new char[n];
		strcpy(s, _s);
	}
}

FSMJson::FSMJson()
{
	n = 1;
	s = new char;
	strcpy(s, "");
}

FSMJson::~FSMJson()
{
	delete[] s;
}

FSMJson::FSMJson(FSMJson &_fsm)
{
	n = _fsm.n;
	delete[] s;
	s = new char[n];
	strcpy(s, _fsm.s);
}

int16_t **FSMJson::FSMMatrix() const
{
	int16_t **fsm=new int16_t*[n];
	for (int i = 0; i < n; ++i)
	{
		fsm[i]=new int16_t[n];
	}
	return fsm;
}
