#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>

namespace animals {
	class Animal {
	protected:
		int no_of_legs;

	public:

		Animal(int no_of_legs = 2);	
		//explicit Animal(int no_of_legs = 2);	//dieser Konstruktor wird explizit aufgerufen, verhindert aufruf vom conversion construktor
		~Animal();

		virtual void make_sound() const;
		int get_no_legs() const;


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
