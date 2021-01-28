#ifndef PERSON_H
#define PERSON_H
#include<iostream>
using std::string;
using std::ostream;

class Person
{
	enum class gender { MALE, FEMALE, OTHER };

private:
	string firstname;
	string surname;
	size_t age;
	string city;
	string creditcardno;

public:
	friend ostream& operator<<(ostream& lhs, Person const& rhs);

	Person(string const& _firstname, string const& _surname, size_t const& _age, string const& _city, string const& _creditcardno)
	{
		firstname = _firstname;
		surname = _surname;
		age = _age;
		city = _city;
		creditcardno = _creditcardno;
	}

};


ostream& operator<<(ostream& lhs, Person const& rhs)
{
	lhs << rhs.firstname << " " << rhs.surname;
	return lhs;

}

#endif