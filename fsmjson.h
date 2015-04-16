//
// Created by ssi on 17.03.15.
//

#ifndef _CLIENT_FSMJSON_H_
#define _CLIENT_FSMJSON_H_
#include <string.h>
#include <stdint.h>

class FSMJson
{
private:
	char *s;
	size_t n;
	char **FSMMatrix() const;
	char **FSMMatrixStates(const size_t &_size = 5) const;
	bool revBoolVar(bool sourse) const;

	static const char MARK_DEF = 0;
	static const char MARK_OPEN_Q_KEY = 1;
	static const char MARK_CLOSE_Q_KEY = 2;
	static const char MARK_OPEN_Q_VALUE = 3;
	static const char MARK_CLOSE_Q_VALUE = 4;
	static const char MARK_MULT = 5;
public:

	FSMJson();
	FSMJson(const char *_s);
	FSMJson(FSMJson &_fsm);
	~FSMJson();
	bool isValidJson(const char *_s) const;
	size_t getNextState(const char *_s, size_t &state, size_t &endIndex, const size_t &startIndex = 0) const;
};


#endif //_CLIENT_FSMJSON_H_
