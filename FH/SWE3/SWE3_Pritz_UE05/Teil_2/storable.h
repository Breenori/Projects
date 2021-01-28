#ifndef STORABLE_H
#define STORABLE_H
#include<iostream>
using std::string;

class Storable
{
	virtual void store(string const& fname) const = 0;
	virtual void load(string const& fname) = 0;
};

#endif