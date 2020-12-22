#ifndef divide_by_zero_h
#define divide_by_zero_h

#include<exception>

class DivideByZeroException : public std::exception {
public:
	virtual const char* what() const throw(){
		return "Divide by 0 Exception!";
	}
};

#endif
