#include "DateTime.h"
#include "flight.h"
#include "flight_journey.h"
#include "Person.h"
#include<iostream>

void test_normal()
{
	Flight f1("F23000", "Dumbo Airlines", "Aegypten", "Berlin", "24.12.2020 08:50:00", "24.12.2020 11:00:00");
	Flight f2("F23001", "Peter Pan Inc.", "London", "Moskau", "24.12.2020 12:00:00", "24.12.2020 14:15:00");
	Flight f3("F23002", "Austrian Airlines", "Wien", "Hagenberg", "24.12.2020 15:10:00", "24.12.2020 16:00:00");

	Person p1("Stefan", "Raab", 44, "Koeln", "DE501203830");
	Person p2("Vladimir", "Klitschko", 10, "Novigrad", "RU2109302314");

	FlightJourney fj({ f1,f2,f3 }, { p1,p2 });
	std::cout << fj;
}
void test_empty()
{
	FlightJourney emptyfj({}, {});
	std::cout << emptyfj;
}
void test_date()
{
	DateTime test("24.12.20201 08:50:00");
	DateTime testfuture("24.12.2021 08:50:00");
	DateTime testpast("24.12.2020 10:00:00");
	std::cout << test << std::endl;
	std::cout << DateTime::diff(testpast, testfuture) << std::endl;
}

void main()
{
	//test_normal();
	//test_empty();
	test_date();
}