#include "renderexception.h"

RenderException::RenderException(std::string _m)
{
	message = _m;
}

RenderException::RenderException(std::string _m, std::string _f, std::string _file, int _l)
{
	message = _m;
	func = _f;
	file = _file;
	line = _l;
}

const char* RenderException::what() const throw()
{
	std::string line_str = std::to_string(line);
	return (nameOfException + ": " + message + " in " + file + "(" + func + ": " + line_str + ")").c_str();
}

RenderException::~RenderException() throw()
{

}
