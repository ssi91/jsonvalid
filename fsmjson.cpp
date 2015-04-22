#include <iostream>
#include "fsmjson.h"
#include "Stack.h"
#include "jsonarraystruct.h"

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

bool FSMJson::isValidJson(const char *_s) const
{
	//TODO экранирование кавычек
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
	bool esCh = false;
	Stack<int> stack(0);
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
			else if ((s[j] == '@') && (mark[j] == MARK_MULT) && qOpened)
			{
				//проверка, что s[j] - буква
				if (_s[j] >= 32 && _s[i] <= 33 || (_s[i] >= 35) && (_s[i] <= 126))
				{
					next_state = j;
					break;
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
//				else if(_s[j]=='"' && esCh)
//				{
//					esCh = false;
//					next_state = j;
//					break;
//				}
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
		//проверка допустимости состояния
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

char **FSMJson::FSMMatrixStates(const size_t &_size) const
{
	char **fsms = new char *[_size];
	for (int i = 0; i < _size; ++i)
	{
		fsms[i] = new char[_size];
		for (int j = 0; j < _size; ++j)
		{
			fsms[i][j] = 0;
		}
	}
	fsms[0][1] = 1;
	fsms[1][2] = 1;
	fsms[2][3] = -1;
	fsms[2][4] = 1;
	fsms[4][1] = 1;
	fsms[4][2] = 1;
	return fsms;
}

size_t FSMJson::getNextState(const char *_s, size_t &state, size_t &endIndex, size_t &startIndex) const
{
	bool isKey = false;
	bool isOpen = false; // true, while open
	bool isNumber = false;
	size_t cur_state = state ? state : 3; //если пришло состояние 0, то устанавливаем его как валидный JSON
	size_t i = startIndex;
	char excChar = '0';
	while (_s[i] != '\0')
	{
		if (cur_state == 4 || cur_state == 3 || cur_state == 2)
		{
			++i;
			if (_s[i] == '"') //получено состояние 1(ключ)
			{
				startIndex = i;
				getLimits(startIndex, endIndex, '"', _s);
				return 1;
			}
			else if ((cur_state == 4 || cur_state == 3) && _s[i] == '{') //получено состояние 3
			{
				startIndex = i;
				getLimits(startIndex, endIndex, '}', _s);
				return 3;
			}
		}
		else if (cur_state == 1)
		{
			++i;
			if (_s[i] == '"')
			{
				startIndex = i;
				getLimits(startIndex, endIndex, '"', _s);
				return 2;
			}
			else if (_s[i] >= '0' && _s[i] <= '9')
			{
				startIndex = i;
				getLimits(startIndex, endIndex, ',', _s);
				return 2;
			}
			else if (_s[i] == '{')
			{
				startIndex = i;
				getLimits(startIndex, endIndex, '}', _s);
				return 3;
			}
			else if (_s[i] == '[')
			{
				startIndex = i;
				getLimits(startIndex, endIndex, ']', _s);
				return 4;
			}
		}
	}

	return 0;
}

bool FSMJson::revBoolVar(bool sourse) const
{
	return !sourse;
}

void FSMJson::setInMap(std::string const &_s)
{
	if (isValidJson(_s.c_str()))
		std::cout << "valid" << std::endl;
	size_t state = 0, endIndex = 0;
	size_t start = 0;
	std::string testStr = _s;
	Stack<JsonArray> stack;
	stack.push({0, _s.length() - 1, 0, 0, _s[0], _s});
	while (endIndex < _s.length() - 1)
	{
		state = getNextState(testStr.c_str(), state, endIndex, start);
		if (state == 3 || state == 4)
		{
			testStr = testStr.substr(start, endIndex - (start - 1));
			JsonArray array = {start, endIndex, 0, 0, testStr[0], testStr};
			stack.push(array);
			endIndex = start = 0;
		}
		else
		{
			if (stack.getCount())
			{
				stack.getTop().curent = endIndex;
				stack.getTop().lastState = state;
			}
			start = endIndex;
		}
	}
}

void FSMJson::getLimits(size_t &start, size_t &end, const char ch, const std::string &_s) const
{
	end = start;
	size_t braces = 0;
	++end;
	while (_s[end] != ch || braces)
	{
		if (ch == '}' && _s[end] == '{' || ch == ']' && _s[end] == '[')
		{
			++braces;
		}
		else if (ch == _s[end])
		{
			--braces;
		}
		++end;
	}
}
//<div style="text-align:left"><img src="http://100hostov.com/sites/354/uploads/images/elementi%20diz%20glavn/04%20elem_diz.jpg" style="border:0px #000000;width:230px;height:33px;vertical-align:baseline"></div><div style="text-align:left"></div><div style="text-align:left"></div><div style="text-align:left"><div></div><div><div><div><div><div>25 - 26.04</div></div></div><div><strong>Открытые региональные соревнования по легкой атлетике памяти&nbsp;С.К.Иконникова&nbsp;</strong></div><div>  <div><strong>г.&nbsp;Асино </strong> <br></div><br></div><div>23 - 26.04</div><div><strong><p text-align:center;text-align:center"="" style="display: inline !important;">Открытое Первенство Томской области «Весенние ласточки»</p></strong></div><div><strong><p text-align:center;text-align:center"="" style="display: inline !important;"> памяти М.Мучника по художественной гимнастике</p></strong></div><div><strong>«Дворец зрелищ и спорта»&nbsp;</strong></div>  <div><br></div><div></div><div><p text-align:center;text-align:center"="" style="display: inline !important;">03.05&nbsp;</p></div><div><strong>Футбол. Первенство ФНЛ&nbsp;</strong></div><div><p text-align:center;text-align:center"="" style="display: inline !important;"><strong>Томь -</strong><strong>&nbsp;Балтика</strong><br></p></div><div><p text-align:center;text-align:center"="" style="display: inline !important;"><strong>стадион "Труд"&nbsp;</strong></p></div>  <div><p text-align:center;text-align:center"="" style="display: inline !important;"><br></p></div><div><p text-align:center;text-align:center"="" style="display: inline !important;">16.05&nbsp;</p></div><div><strong>Футбол. Первенство ФНЛ&nbsp;</strong></div><div><p text-align:center;text-align:center"="" style="display: inline !important;"><strong>Томь -</strong><strong>&nbsp;Волгарь</strong><br></p></div><div><p text-align:center;text-align:center"="" style="display: inline !important;"><strong>стадион "Труд"&nbsp;</strong></p></div>  <div><p text-align:center;text-align:center"="" style="display: inline !important;"><br></p></div><div><div><p text-align:center;text-align:center"="" style="display: inline !important;">17.05&nbsp;</p></div><div><strong>«Российский Азимут»&nbsp;.&nbsp;Всероссийские&nbsp;соревнования&nbsp;</strong></div><div><strong>по спортивному ориентированию&nbsp;</strong><br></div><div><p text-align:center;text-align:center"="" style="display: inline !important;"><strong>Нижняя&nbsp;терраса&nbsp;Лагерного сада</strong></p></div>  <p text-align:center;text-align:center"="" style="display: inline !important;"><br></p></div><div><p text-align:center;text-align:center"="" style="display: inline !important;">30.05&nbsp;</p></div><div><strong>Футбол. Первенство ФНЛ&nbsp;</strong></div><div><p text-align:center;text-align:center"="" style="display: inline !important;"><strong>Томь -</strong><strong>&nbsp;Динамо</strong><br></p></div><div><p text-align:center;text-align:center"="" style="display: inline !important;"><strong>стадион "Труд"&nbsp;</strong></p></div>  <p text-align:center;text-align:center"=""><br></p><p style="font-weight: bold;" text-align:center;text-align:center"=""><strong>&nbsp;</strong></p>  <br></div><div><a href="http://sportus.pro/%D0%A1%D0%BF%D0%BE%D1%80%D1%82%D0%B8%D0%B2%D0%BD%D0%B0%D1%8F%20%D0%B0%D1%84%D0%B8%D1%88%D0%B0">Все спортивные события</a></div>  <br></div>  </div>