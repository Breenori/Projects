#include "zoo.h"

using std::vector;

Zoo::Zoo()
{
}

void Zoo::add_animal(animals::Animal* animal)
{
	animals.push_back(animal);
}

std::vector<animals::Animal*>& Zoo::get_animals()
{
	return animals;
}
