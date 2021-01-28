#ifndef ANIMAL_H
#define ANIMAL_H
#include<string>

enum species_t {donkey, cat, dog, spider};

class animal_t {
private:
	std::string name;
	size_t age;
	species_t type;
	static int NUMBER_OF_ANIMALS;

public:
	void set_name(std::string name);
	void set_age(size_t age);
	void set_type(species_t type);
	std::string get_name() const;
	size_t get_age() const;
	species_t get_type() const;
	void make_sound() const;
	animal_t();
	animal_t(std::string name, size_t age, species_t type);
	static int get_number_of_animals();
};
#endif