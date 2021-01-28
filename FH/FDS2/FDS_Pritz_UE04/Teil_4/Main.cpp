#include "list_number.h"
#include<iostream>

// Prints whether one number is bigger than another.
void print_info(list_number_t const& l1, list_number_t const& l2);
// Tests several values in terms of comparing them.
void test_functionality_cmp();

void main()
{
	test_functionality_cmp();

	//list_number_t l4("-10000");
	//list_number_t l5("Hallo!");
	//list_number_t zero1;
	//list_number_t zero2;
	//print_info(zero1, zero2);
}

void print_info(list_number_t const& l1, list_number_t const& l2)
{
	int res(l1.compare(l2));
	l1.print();
	if (res == -1)
	{
		std::cout << " is less than ";
	}
	else if (res == 0)
	{
		std::cout << " is equal to ";
	}
	else
	{
		std::cout << " is greater than ";
	}
	std::cout << std::endl;
	l2.print();
}

void test_functionality_cmp()
{
	list_number_t l1("21938219845");
	list_number_t l2("12381298549219204931209");
	list_number_t l3("12381298549219204931209");

	l1.print();
	l2.print();
	l3.print();
	std::cout << std::endl;

	print_info(l1, l2);
	std::cout << std::endl;
	print_info(l2, l3);
	std::cout << std::endl;
	print_info(l3, l1);
	std::cout << std::endl;

	l3.set_sign(list_number_t::sign_t::SIGN_NEGATIVE);
	print_info(l2, l3);
}
