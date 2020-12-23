#include "animal.h"
#include <vector>
#include "statistics.h"
#include "zoo.h"

using animals::Animal;
using animals::Donkey;
using animals::Sheep;
using animals::Bird;
using std::vector;

void test_animal(const Animal& animal) {
	std::cout << "No. of legs: " << animal.get_no_legs() << " , making sound: " << std::endl;
	animal.make_sound();
}

void test_donkey(const Donkey& donkey)
{
	std::cout << "No. of legs: " << donkey.get_no_legs() << " , making sound: " << std::endl;
	donkey.make_sound();
}

void test_sheep(const Sheep& sheep)
{
	std::cout << "No. of legs: " << sheep.get_no_legs() << " , making sound: " << std::endl;
	sheep.make_sound();
}

void test_bird(const Bird& bird)
{
	std::cout << "No. of legs: " << bird.get_no_legs() << " , making sound: " << std::endl;
	bird.make_sound();
	bird.fly();
}
// Bad --> Slicing of derived types (donkey, sheep, bird..)
void test_make_sound(const Animal& a)
{
	std::cout << "No. of legs: " << a.get_no_legs() << " , making sound: " << std::endl;
	a.make_sound();
}

void test_make_sounds(const vector<Animal*>& animals)
{
	std::cout << ">test_make_sounds(vector<Animal>):\n";
	for (size_t i(0); i < animals.size(); i++)
	{
		std::cout << i << ": " << animals[i]->get_no_legs() << " ";
		animals[i]->make_sound();
	}
}

void is_of_type(const Animal* animal)
{
	std::cout << "----------------------------------\n";
	const Donkey* donkey = dynamic_cast<const Donkey*>(animal);
	if (donkey == nullptr)
	{
		std::cout << "The given animal object is no donkey \n";
	}
	else
	{
		std::cout << "The given animal is a donkey: ";
		test_make_sound(*donkey);
	}

	const Sheep* sheep = dynamic_cast<const Sheep*>(animal);
	if (sheep == nullptr)
	{
		std::cout << "The given animal object is no sheep \n";
	}
	else
	{
		std::cout << "The given animal is a sheep: ";
		test_make_sound(*sheep);
	}

	const Bird* bird = dynamic_cast<const Bird*>(animal);
	if (bird == nullptr)
	{
		std::cout << "The given animal object is no bird. \n";
	}
	else
	{
		std::cout << "The given animal is a bird: ";
		test_make_sound(*bird);
		bird->fly();
	}

}

void main(){

	Animal a(4);

	test_animal(a);

	Animal b = 6;	//calls impoicitly Animal(6)
	//Animal c= "6"; //does not work, because ther is not valid constructor
	test_animal(6);

	Donkey c;
	test_donkey(c);

	Sheep d;
	test_sheep(d);

	Bird e;
	test_bird(e);

	std::cout << "---------------------\n";
	test_make_sound(a);
	test_make_sound(c);
	test_make_sound(d);
	std::cout << "---------------------\n";
	vector<Animal*> animals;
	animals.push_back(&a);
	animals.push_back(&c);
	animals.push_back(&d);
	animals.push_back(&e);
	test_make_sounds(animals);

	std::cout << "----------------------\n";
	Zoo z;
	z.add_animal(&a);
	z.add_animal(&c);
	z.add_animal(&d);
	z.add_animal(&e);

	Statistics statistics;
	statistics.print_nutrition_stats(z.get_animals());

	is_of_type(&e);
}