#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>


namespace animals {

	class Organism
	{
	public:
		// pure virtual function = abstract
		virtual double metabolism_rate() const = 0;
	};

	class Animal : Organism {
	protected:
		int no_of_legs;
		std::string nutrition;
	public:

		Animal(int no_of_legs = 2);	
		//explicit Animal(int no_of_legs = 2);	//dieser Konstruktor wird explizit aufgerufen, verhindert aufruf vom conversion construktor
		~Animal();

		virtual void make_sound() const;
		virtual double metabolism_rate() const override;
		int get_no_legs() const;
		std::string get_nutrition() const;


	};

	class Donkey : public Animal
	{
	public:
		Donkey();
		// Override prüft ob signatur zur basisklasse passt.
		void make_sound() const override;
	};

	class Sheep : public Animal
	{
	public:
		Sheep();
		void make_sound() const;
	};

	class Bird : public Animal
	{
	public:
		Bird();
		void make_sound() const;
		void fly() const;
	};
}



#endif // !ANIMAL_H
