#include<iostream>
#include<vector>
#include<string>
#include "car.h"
#include "filter_operations.h"

using std::cout;
using std::vector;
using std::string;

void print_vector(vector<Car*> const& cars)
{
	for (auto it = cars.begin(); it != cars.end(); ++it)
	{
		cout	<< "Car[ color: "		<< (*it)->get_color()
				<< ", fuel: "			<< (*it)->get_fuel()
				<< ", horse_power: "	<< (*it)->get_horse_power()
				<< ", tank_volume: "	<< (*it)->get_tank_volume() << " ]\n";
	}
}

// VErsion 1
// call filter function
void test_callables_v1()
{
	Car a("red", "fuel roz 95", 200, 48);
	Car b("blue", "fuel roz 98", 110, 53);
	Car c("green", "diesel", 125, 44);
	Car d("red", "electric", 400, 50);

	vector<Car*> cars = { &a, &b, &c, &d };
	cout << "Filter with function: \n";
	filter_ops::filter_color(cars, "red");

	print_vector(cars);
}


bool eval_color_green(string color)
{
	return color == "green";
}


// Version 2
// call filter using function pointer
void test_callables_v2()
{
	Car a("red", "fuel roz 95", 200, 48);
	Car b("blue", "fuel roz 98", 110, 53);
	Car c("green", "diesel", 125, 44);
	Car d("red", "electric", 400, 50);

	vector<Car*> cars = { &a, &b, &c, &d };
	cout << "Filter with function pointer: \n";
	filter_ops::fun_t fn(eval_color_green);
	filter_ops::filter_color(cars, fn);

	print_vector(cars);
}

// use functor
void test_callables_v3()
{
	Car a("red", "fuel roz 95", 200, 48);
	Car b("blue", "fuel roz 98", 110, 53);
	Car c("green", "diesel", 125, 44);
	Car d("red", "electric", 400, 50);

	vector<Car*> cars = { &a, &b, &c, &d };
	cout << "Filter with functor: \n";

	filter_ops::ColorPredicate p("blue");
	filter_ops::filter_color(cars, p);

	print_vector(cars);
}

// Lambda expressions: [capture](params){body}
// Capture = Welche Variablen aus dem Umgebenden Block sollen sichtbar sein? --> WErte zum Zeitpunkt DER DEFINITION der expression.
// Params/Body = gleich wie funktionen

// use lambda
void test_callables_v4()
{
	Car a("red", "fuel roz 95", 200, 48);
	Car b("blue", "fuel roz 98", 110, 53);
	Car c("green", "diesel", 125, 44);
	Car d("red", "electric", 400, 50);

	vector<Car*> cars = { &a, &b, &c, &d };
	cout << "Filter with lambda: \n";

	filter_ops::filter_color(cars, [](Car& c) { return c.get_horse_power() > 120; });

	print_vector(cars);
}


int main()
{
	test_callables_v1();
	test_callables_v2();
	test_callables_v3();
	test_callables_v4();
	return 0;
}

