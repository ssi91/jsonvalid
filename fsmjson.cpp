#include <iostream>
#include "fsmjson.h"
#include "stack.h"

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
	std::cout << n << std::endl;
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

char **FSMJson::FSMMatrix() const
{
	char **fsm = new char *[n - 1];
	for (int i = 0; i < n - 1; ++i)
	{
		fsm[i] = new char[n];
		for (int j = 0; j < n; ++j)
		{
			fsm[i][j] = 0;
		}
	}
	fsm[0][1] = 1;
	fsm[1][2] = 1;
	fsm[1][5] = 1;
	fsm[1][10] = 1;
	fsm[2][2] = 1;
	fsm[2][4] = 1;
	fsm[2][5] = 1;
	fsm[2][10] = 1;
	fsm[2][12] = 1;
	fsm[3][0] = 1;
	fsm[3][4] = 1;
	fsm[3][7] = 1;
	fsm[3][11] = 1;
	fsm[4][2] = 1;
	fsm[4][4] = 1;
	fsm[4][5] = 1;
	fsm[4][9] = 1;
	fsm[4][10] = 1;
	fsm[4][12] = 1;
	fsm[5][3] = 1;
	fsm[6][6] = 1;
	fsm[6][8] = 1;
	fsm[6][9] = 1;
	fsm[6][13] = -1;
	fsm[7][0] = 1;
	fsm[7][11] = 1;
	fsm[8][6] = 1;
	fsm[9][0] = 1;
	fsm[9][1] = 1;
	fsm[10][2] = 1;
	fsm[10][4] = 1;
	fsm[10][5] = 1;
	fsm[10][10] = 1;
	fsm[10][11] = 1;
	fsm[10][12] = 1;
	fsm[11][2] = 1;
	fsm[11][4] = 1;
	fsm[11][10] = 1;
	fsm[11][12] = 1;
	fsm[12][6] = 1;
	fsm[12][8] = 1;
	fsm[12][9] = 1;
	return fsm;
}

bool FSMJson::isValidJson(const char *_s1) const
{
//	char _s[] = "{\"key\":\"value\"}";
//	char _s[] = "{\"key\":[{\"key\":\"oauth\",\"value\":\"1\"},{\"key\":\"method\",\"value\":\"messages.get\"}]}";
	char _s[] = "{\"error\":{\"error_code\":5,\"error_msg\":\"User authorization failed invalid session.\",\"request_params\":[{\"key\":\"oauth\",\"value\":\"1\"},{\"key\":\"method\",\"value\":\"messages.get\"},{\"key\":\"out\",\"value\":\"0\"},{\"key\":\"count\",\"value\":\"1\"},{\"key\":\"user_id\",\"value\":\"9556448\"},{\"key\":\"v\",\"value\":\"5.27\"},{\"key\":\"access_token\",\"value\":\"9efd022746e646c729c3d7abed71293671aeab43ecf2675b1f9a0af19e8f1a8407ee542c3e6de10044993\"}]}}";
	std::cout << _s << std::endl;

	char **fsm = FSMMatrix();
	size_t size = n - 1;
	size_t i = 0;
	char mark[13] = {0, 1, 5, 0, 5, 2, 0, 0, 0, 0, 0, 3, 4};
	size_t cur_state = 0;
	size_t next_state;
	bool isKey = true; // if false - value
	bool qOpened = false; //if opened - true
	bool startState = true;
	bool brackes = true; //false if was '[', else '{'
	Stack stack(0);
	while (_s[i] != '\0')
	{
		//определение пришедшего состояния next_state
		for (int j = 0; j < size; ++j)
		{
			if ((s[j] == _s[i]) && (mark[j] == MARK_DEF))
			{
				if ((s[j] == '[' || s[j] == '}' || s[j] == ']' || s[j] == '{' || s[j] == ',') && !isKey)
					isKey = true;

				if (s[j] == '{')
				{
					if (brackes)
					{
						stack.incTop();
					}
					else
					{
						stack.push(1);
						brackes = true;
					}
				}
				else if (s[j] == '[')
				{
					if (!brackes)
					{
						stack.incTop();
					}
					else
					{
						stack.push(1);
						brackes = false;
					}
				}
				else if (s[j] == '}')
				{
					if (brackes)
					{
						stack.decTop();
						int top = stack.pop();
						if (top)
							stack.push(top);
						else
							brackes = false;
					}
					else
					{
						//TODO освободить память и вернуть false
						for (int k = 0; k < n - 1; ++k)
						{
							delete[] fsm[k];
						}
						delete[] fsm;
						return false;
					}
				}
				else if (s[j] == ']')
				{
					if (!brackes)
					{
						stack.decTop();
						int top = stack.pop();
						if (top)
							stack.push(top);
						else
							brackes = true;
					}
					else
					{
						//TODO освободить память и вернуть false
						for (int k = 0; k < n - 1; ++k)
						{
							delete[] fsm[k];
						}
						delete[] fsm;
						return false;
					}
				}

				next_state = j;
				break;
			}
			else if ((s[j] == '@') && (mark[j] == MARK_MULT))
			{
				//проверка, что s[j] - буква
				if ((_s[i] >= 65) && (_s[i] <= 90) || (_s[i] >= 97) && (_s[i] <= 122) || (_s[i]) == '_')
				{
					next_state = j;
					break;
				}
			}
			else if ((s[j] == '#') && (mark[j] == MARK_MULT))
			{
				//проверка, что s[j] - цифра
				if ((_s[i] >= 48) && (_s[i] <= 57))
				{
					next_state = j;
					break;
				}
			}
			else if ((s[j] == _s[i]) && (s[j] == '"'))
			{
				char wontState = -1;
				if (isKey)
				{
					if (!qOpened)
					{
						wontState = MARK_OPEN_Q_KEY; //я хочу состояние с такой меткой
						qOpened = true;
					}
					else
					{
						wontState = MARK_CLOSE_Q_KEY;
						qOpened = false;
						isKey = false;
					}
				}
				else
				{
					if (!qOpened)
					{
						wontState = MARK_OPEN_Q_VALUE; //я хочу состояние с такой меткой
						qOpened = true;
					}
					else
					{
						wontState = MARK_CLOSE_Q_VALUE;
						qOpened = false;
					}
				}
				if (mark[j] != wontState)
				{
					for (int k = 0; k < size; ++k)
					{
						if (mark[k] == wontState)
						{
							j = k;
							break;
						}
					}
				}
				next_state = j;
				break;
			}
		}
		//TODO проверка правильности пришедшего состояния
		if (startState)
		{
			startState = false;
			cur_state = next_state;
		}
		else
		{
			if (fsm[cur_state][next_state] == 1)
			{
				cur_state = next_state;
			}
			else
			{
				for (int k = 0; k < n - 1; ++k)
				{
					delete[] fsm[k];
				}
				delete[] fsm;
				return false;
			}
		}
		i++;
	}
	if (fsm[cur_state][size] != -1 || stack.getCount())
		return false;
	for (int i = 0; i < n - 1; ++i)
	{
		delete[] fsm[i];
	}
	delete[] fsm;
	return true;
}