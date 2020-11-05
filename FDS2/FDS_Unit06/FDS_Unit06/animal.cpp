#include "animal.h"
#include<iostream>
using std::cout;

int animal_t::NUMBER_OF_ANIMALS = 0;

void animal_t::set_name(std::string name)
{
	this->name = name;
}
void animal_t::set_age(size_t age)
{
	this->age = age;
}
void animal_t::set_type(species_t type)
{
	this->type = type;
}
std::string animal_t::get_name() const
{
	return this->name;
}
size_t animal_t::get_age() const
{
	return this->age;
}
species_t animal_t::get_type() const
{
	return this->type;
}
void animal_t::make_sound() const
{
	cout << name << " says: ";
	switch (type)
	{
	case donkey:
		cout << "Poo, that isn't honey.\n";
		break;
	case dog:
		cout << "EDWARD.\n";
		break;
	case cat:
		cout << "MIAUZ GENAU!\n";
		break;
	case spider:
		cout << "*angry spider noises*\n";
		break;
	default:
		cout << "*angry unidentified species noises*";
		break;
	}
}

animal_t::animal_t() : animal_t("Biscuitroulade", 0, donkey)
{

}


animal_t::animal_t(std::string name, size_t age, species_t type)
{
	this->name = name;
	this->age = age;
	this->type = type;
	NUMBER_OF_ANIMALS++;
}

int animal_t::get_number_of_animals()
{
	return NUMBER_OF_ANIMALS;
}
