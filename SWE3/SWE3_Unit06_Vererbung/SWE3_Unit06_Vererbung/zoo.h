
#include<vector>
#include<iostream>
#include "animal.h"

class Zoo
{
private:
	std::vector<animals::Animal*> animals;
public:
	Zoo();
	void add_animal(animals::Animal* animal);
	std::vector<animals::Animal*>& get_animals();
};
