#ifndef car_h
#define car_h
#include<iostream>

class Car
{
public:
	Car(std::string color, std::string fuel, int horse_power, int tank_volume) : 
		color(color), 
		fuel(fuel), 
		horse_power(horse_power), 
		tank_volume(tank_volume){ }

	std::string const& get_color() const;
	std::string const& get_fuel() const;
	int const& get_horse_power() const;
	int const& get_tank_volume() const;
private:
	std::string color;
	std::string fuel;
	int horse_power;
	int tank_volume;
};

#endif