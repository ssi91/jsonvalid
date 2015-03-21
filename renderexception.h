#ifndef RENDEX_H
#define RENDEX_H
#define LOG_TRACE(ERROR) new RenderException(ERROR, __FUNCTION__, __FILE__, __LINE__);
#include <iostream>
#include <exception>
#include <string>

class RenderException : public std::exception
{
	private:
		std::string message;
		std::string func;
		std::string file;
		int line;
	protected:
		std::string nameOfException = "RenderException";
	public:
		RenderException(std::string _m = "");
		RenderException(std::string _m, std::string _f, std::string _file, int _l);
		virtual const char* what() const throw();
		virtual ~RenderException() throw();
};
#endif
