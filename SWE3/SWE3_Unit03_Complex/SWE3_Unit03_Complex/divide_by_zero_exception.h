#ifndef DIVIDE_BY_ZERO_EXCEPTION_H
#define DIVIDE_BY_ZERO_EXCEPTION_H

#include<exception>
using std::exception;

class DivideByZeroException : public exception {
public:
	virtual const char* what() const throw() {
		return "Divide by 0 Exception";
	}
};

#endif