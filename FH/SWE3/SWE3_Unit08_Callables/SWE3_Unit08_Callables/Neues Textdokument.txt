#include "car.h"

using std::string;

string const& Car::get_color() const
{
	return color;
}

string const& Car::get_fuel() const
{
	return fuel;
}

int const& Car::get_horse_power() const
{
	return horse_power;
}

int const& Car::get_tank_volume() const
{
	return tank_volume;
}