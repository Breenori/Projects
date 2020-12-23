#ifndef PERSON_H
#define PERSON_H
#include<iostream>
using std::string;

class Person
{
	enum class gender { MALE, FEMALE, OTHER };
	struct address_t {
		string street;
		size_t no;
		size_t postal;
		string city;
	};

private:
	string firstname;
	string surname;
	size_t age;
	address_t address;
	string creditcardno;

};


#endif