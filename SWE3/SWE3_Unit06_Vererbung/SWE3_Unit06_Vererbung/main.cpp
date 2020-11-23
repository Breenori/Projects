#include "animal.h"
#include <vector>

using animals::Animal;
using animals::Donkey;
using animals::Sheep;
using animals::Bird;

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
}