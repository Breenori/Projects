#include "C.h"

C::C()
{
	this->i = 0;
	this->d = 0;
}

void C::set_i(int j)
{
	this->i = j;
}

void C::set_d(double d)
{
	this->d = d;
}

void C::print_all(std::ostream& o) 
{
	o << i << ", " << d << "\n";
}
