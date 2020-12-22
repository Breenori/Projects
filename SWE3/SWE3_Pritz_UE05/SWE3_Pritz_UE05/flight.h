#ifndef FLIGHT_H
#define FLIGHT_H
#include<iostream>
#include<vector>
#include "datetime.h"
#include "person.h"
using std::string;
using std::vector;

class flight
{

private:
	size_t flightno;
	string airline;
	string origin;
	string destination;
	DateTime departure;
	DateTime arrival;

	vector<Person*> people;
	


};

#endif