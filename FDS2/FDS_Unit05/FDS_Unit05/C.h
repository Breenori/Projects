#if !defined C_H
#define	C_H

#include <iostream>

class C {

private:
	int i;
	double d;

public:
	void set_i(int j);
	void set_d(double d);
	C();
	void print_all(std::ostream& o);
};

#endif

