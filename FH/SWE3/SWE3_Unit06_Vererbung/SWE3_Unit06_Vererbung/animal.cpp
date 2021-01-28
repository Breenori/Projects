#include "animal.h"


using animals::Animal;
using animals::Donkey;
using animals::Sheep;
using animals::Bird;

Animal::Animal(int no_of_legs ) {
	this->no_of_legs = no_of_legs;
	this->nutrition = "omnivore";
}

Animal::~Animal() {

}


void Animal::make_sound() const{
	std::cout << "ROOOOOOOOOOOOOOOOAAAAARRRRRRRR" << "\n";
}

double animals::Animal::metabolism_rate() const
{
	return 13.37;
}

int Animal::get_no_legs() const {
	return no_of_legs;
}

std::string animals::Animal::get_nutrition() const
{
	return nutrition;
}

Donkey::Donkey() : Animal(4)
{
	nutrition = "herbivore";
}

void Donkey::make_sound() const
{
	std::cout << "II-AAAAAAAAAAAAAAAAAHHHHHHHHHHHHHHHHH" << "\n";
}

Sheep::Sheep()
{
	no_of_legs = 4;
	nutrition = "herbivore";
}

void Sheep::make_sound() const
{
	std::cout << "BAAAAAAAAAAAAAAAAAAAAAHHHHHHHHHHHH" << "\n";
}

Bird::Bird() : Animal(2)
{

}

void Bird::make_sound() const
{
	std::cout << "TWEEEEEEEEEEET TWEEEEEEEEEET" << "\n";
}

void Bird::fly() const
{
	std::cout << "'Human-kun, baka!' -- *BLUSHES AND FLIES AWAY*" << "\n";
}