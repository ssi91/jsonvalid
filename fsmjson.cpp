#include <iostream>
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
	fsm[3][7] = 1;
	fsm[3][11] = 1;
	fsm[4][2] = 1;
	fsm[4][4] = 1;
	fsm[4][5] = 1;
	fsm[4][9] = 1;
	fsm[4][12] = 1;
	fsm[5][3] = 1;
	fsm[6][6] = 1;
	fsm[6][8] = 1;
	fsm[6][9] = 1;
	fsm[6][13] = -1;
	fsm[7][0] = 1;
	fsm[7][11] = 1;
	fsm[8][6] = 1;
	fsm[9][11] = 1;
	fsm[10][2] = 1;
	fsm[10][4] = 1;
	fsm[10][5] = 1;
	fsm[10][10] = 1;
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

bool FSMJson::isValidJson(const char *_s) const
{
	char **fsm = FSMMatrix();
	size_t size = n - 1;
	size_t i = 0;
	char mark[13] = {0, 1, 5, 0, 5, 2, 0, 0, 0, 0, 0, 3, 4};
	size_t cur_state, next_state;
	bool isKey = true; // if false - value
	bool qOpened = false; //if opened - true

	while (_s[i] != '\0')
	{
		if (!i)
		{
			cur_state = 0;
		}
		else
		{
			//определение пришедшего состояния next_state
			for (int j = 0; j < size; ++j)
			{
				if ((s[j] == _s[i]) && (mark[j] == FSMJson::MARK_DEF))
				{
					next_state = j;
					break;
				}
				else if ((s[j] == '@') && (mark[j] == FSMJson::MARK_MULT))
				{
					//проверка, что s[j] - буква
					if ((_s[i] >= 65) && (_s[i] <= 90) || (_s[i] >= 97) && (_s[i] <= 122))
					{
						next_state = j;
						break;
					}
				}
				else if ((s[j] == '#') && (mark[j] == FSMJson::MARK_MULT))
				{
					//проверка, что s[j] - цифра
					if ((_s[i] >= 48) && (_s[i] <= 57))
					{
						next_state = j;
						break;
					}
				}
				else
				{
					//TODO обработка кавычек
				}
			}
			//TODO проверка правильности пришедшего состояния
			for (int j = 0; j < size; ++j)
			{
				if ((fsm[cur_state][j] == 1) && (j == next_state))
				{
					cur_state = next_state;
					break;
				}
				else if (j == size - 1)
				{
					return false;
				}
			}
		}
		i++;
	}
	return true;
}