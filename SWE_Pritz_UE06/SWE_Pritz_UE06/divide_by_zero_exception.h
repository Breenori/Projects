#ifndef DIVIDE_BY_ZERO_EXCEPTION_H
#define DIVIDE_BY_ZERO_EXCEPTION_H
#include<exception>

class divide_by_zero_exception : public std::exception
{
public:
	virtual const char* what() const throw() 
	{
		return "Divide by 0 exception";
	}
};

#endif