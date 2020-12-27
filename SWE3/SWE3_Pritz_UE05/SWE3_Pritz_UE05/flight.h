#ifndef FLIGHT_H
#define FLIGHT_H
#include<iostream>
#include<vector>
#include "datetime.h"
#include "person.h"
#include<iostream>
using std::string;
using std::vector;
using std::ostream;

class Flight
{

private:
	string flightno;
	string airline;
	string origin;
	string destination;
	DateTime departure;
	DateTime arrival;
	DateTime duration;

public:
	friend ostream& operator<<(ostream& lhs, Flight const& rhs);
	
	Flight(string const& flightno, string const& airline, string const& origin, string const& destination, string const& dep, string const& arr)
	{
		this->flightno = flightno;
		this->airline = airline;
		this->origin = origin;
		this->destination = destination;
		this->departure = DateTime(dep);
		this->arrival = DateTime(arr);
		this->duration = DateTime::diff(departure, arrival);
	}
};

ostream& operator<<(ostream& lhs, Flight const& rhs)
{
	lhs << rhs.origin << " -> " << rhs.destination;
	return lhs;
}

#endif