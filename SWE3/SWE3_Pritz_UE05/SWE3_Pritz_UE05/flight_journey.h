#ifndef FLIGHT_JOURNEY_H
#define FLIGHT_JOURNEY_H
#include "flight.h"
#include "person.h"
#include<vector>
#include<iostream>
using std::vector;
using std::ostream;

class FlightJourney{
private:
	vector<Flight> flights;
	vector<Person> people;
	
public:
	friend ostream& operator<<(ostream& lhs, FlightJourney const& rhs);
	
	FlightJourney(vector<Flight> const& flights, vector<Person> const& people)
	{
		this->flights = flights;
		this->people = people;
	}

	void printFlights(ostream& out = std::cout) const
	{
		if(flights.size() == 0)
		{
			out << "No flights found for this journey.\n";
		}
		else
		{
			for (int i(0); i < flights.size(); i++)
			{
				if (i > 0)
				{
					out << " -> ";
				}
				out << flights[i];
			}
			out << std::endl;
		}
	}
	void printPeople(ostream& out = std::cout) const
	{
		if(people.size() == 0)
		{
			out << "No people attending this journey.\n";
		}
		else
		{
			for (int i(0); i < people.size(); i++)
			{
				if (i > 0)
				{
					out << ", ";
				}
				out << people[i];
			}
			out << std::endl;
		}
	}
	

};

ostream& operator<<(ostream& lhs, FlightJourney const& rhs)
{
	rhs.printFlights(lhs);
	rhs.printPeople(lhs);
	return lhs;
}

#endif