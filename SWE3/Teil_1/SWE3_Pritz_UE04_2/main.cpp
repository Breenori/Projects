#include "rational_type.h"
#include "divide_by_zero_exception.h"
#include<iostream>
#include<fstream>

void test_reference()
{
	rational_t r(-1, 2);

	std::cout	<< r * -10 << std::endl
				<< r * rational_t(20, -2)	<< std::endl;

	r = 7;

	std::cout	<< r + rational_t(2, 3)				<< std::endl
				<< 10 / r / 2 + rational_t(6, 5)	<< std::endl;

	std::cout << std::endl;
}

void test_constructors()
{
	std::cout << "Default constructor: " << rational_t() << std::endl;
	std::cout << "Default constructor: " << rational_t(10) << std::endl;
	std::cout << "Default constructor : " << rational_t(10, 100) << std::endl;

	std::cout << std::endl;
}

void test_add()
{
	rational_t r1(1, 2);
	rational_t r2(1, 4);

	rational_t r3 = r1 + r2;

	rational_t r4 = r1;
	r4 += r2;
	std::cout << r1 << " + " << r2 << " (normal vs assign): " << r3 << " = " << r4 << std::endl;

	r4 += 1;
	r3 = r3 + 1;
	std::cout << "Both plus 1 (normal vs assign): " << r3 << " = " << r4 << std::endl;

	std::cout << std::endl;
}
void test_sub()
{
	rational_t r1(1, 2);
	rational_t r2(1, 4);

	rational_t r3 = r1 - r2;

	rational_t r4 = r1;
	r4 -= r2;
	std::cout << r1 << " - " << r2 << " (normal vs assign): " << r3 << " = " << r4 << std::endl;

	r4 -= 1;
	r3 = r3 - 1;
	std::cout << "Both minus 1 (normal vs assign): " << r3 << " = " << r4 << std::endl;

	std::cout << std::endl;
}
void test_mul()
{
	rational_t r1(1, 2);
	rational_t r2(1, 2);

	rational_t r3 = r1 * r2;

	rational_t r4 = r1;
	r4 *= r2;
	std::cout << r1 << " * " << r2 << " (normal vs assign): " << r3 << " = " << r4 << std::endl;

	r4 *= 2;
	r3 = 2 * r3;
	std::cout << "Both multiplied by 2 (normal vs assign): " << r3 << " = " << r4 << std::endl;

	std::cout << std::endl;
}
void test_div()
{
	rational_t r1(7, 18);
	rational_t r2(1, 2);

	rational_t r3 = r1 / r2;

	rational_t r4 = r1;
	r4 /= r2;
	std::cout << r1 << " * " << r2 << " (normal vs assign): " << r3 << " = " << r4 << std::endl;

	r4 /= 2;
	r3 = r3 / 2;
	std::cout << "Both divided by 2 (normal vs assign): " << r3 << " = " << r4 << std::endl;

	std::cout << std::endl;
}

void test_comparison()
{
	rational_t r1(1, 2);
	rational_t r2(12, 36);

	std::cout << "Comparison of unequal rationals: " << std::endl;
	std::cout << r1.as_string() + " == " + r2.as_string() << ": " << (r1 == r2 ? "YES" : "NO") << std::endl;
	std::cout << r1.as_string() + " != " + r2.as_string() << ": " << (r1 != r2 ? "YES" : "NO") << std::endl;
	std::cout << r1.as_string() + " <  " + r2.as_string() << ": " << (r1 <  r2 ? "YES" : "NO") << std::endl;
	std::cout << r1.as_string() + " <= " + r2.as_string() << ": " << (r1 <= r2 ? "YES" : "NO") << std::endl;
	std::cout << r1.as_string() + " >  " + r2.as_string() << ": " << (r1 >  r2 ? "YES" : "NO") << std::endl;
	std::cout << r1.as_string() + " >= " + r2.as_string() << ": " << (r1 >= r2 ? "YES" : "NO") << std::endl;
	std::cout << std::endl;

	r2 = rational_t(1, 2);
	std::cout << "Comparison of equal rationals: " << std::endl;
	std::cout << r1.as_string() + " == " + r2.as_string() << ": " << (r1 == r2 ? "YES" : "NO") << std::endl;
	std::cout << r1.as_string() + " != " + r2.as_string() << ": " << (r1 != r2 ? "YES" : "NO") << std::endl;
	std::cout << r1.as_string() + " <  " + r2.as_string() << ": " << (r1 < r2 ? "YES" : "NO") << std::endl;
	std::cout << r1.as_string() + " <= " + r2.as_string() << ": " << (r1 <= r2 ? "YES" : "NO") << std::endl;
	std::cout << r1.as_string() + " >  " + r2.as_string() << ": " << (r1 > r2 ? "YES" : "NO") << std::endl;
	std::cout << r1.as_string() + " >= " + r2.as_string() << ": " << (r1 >= r2 ? "YES" : "NO") << std::endl;

	std::cout << std::endl;
}

void test_signfunctions()
{
	rational_t r1(-3, -7);
	rational_t r2(-21, 4);
	rational_t r3(0, 33);

	std::cout << "Is" << r1.as_string() << " positive? " << (r1.is_positive()	? "YES" : "NO") << std::endl;
	std::cout << "Is" << r1.as_string() << " negative? " << (r1.is_negative()	? "YES" : "NO") << std::endl;
	std::cout << "Is" << r1.as_string() << " zero?     " << (r1.is_zero()		? "YES" : "NO") << std::endl;
	std::cout << std::endl;
	std::cout << "Is" << r2.as_string() << " positive? " << (r2.is_positive() ? "YES" : "NO") << std::endl;
	std::cout << "Is" << r2.as_string() << " negative? " << (r2.is_negative() ? "YES" : "NO") << std::endl;
	std::cout << "Is" << r2.as_string() << " zero?     " << (r2.is_zero() ? "YES" : "NO") << std::endl;
	std::cout << std::endl;
	std::cout << "Is" << r3.as_string() << " positive? " << (r3.is_positive() ? "YES" : "NO") << std::endl;
	std::cout << "Is" << r3.as_string() << " negative? " << (r3.is_negative() ? "YES" : "NO") << std::endl;
	std::cout << "Is" << r3.as_string() << " zero?     " << (r3.is_zero() ? "YES" : "NO") << std::endl;

	std::cout << std::endl;
}

void test_IO()
{
	rational_t r1;
	
	std::ifstream in("rational.txt");
	in >> r1;
	std::cout << "From populated file:	" << r1 << std::endl;
	in.close();

	std::cout << std::endl;

	in.open("empty.txt");
	in >> r1;
	std::cout << "From empty file:	" << r1 << std::endl;
	in.close();

	std::cout << std::endl;
}

void test_exception()
{
	int num(1);
	int den(0);
	rational_t r1;

	std::cout << "Trying to create rational <1/0>: \n";
	try {
		 r1 = rational_t(num, den);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		r1 = rational_t(num);
	}

	std::cout << std::endl;

	std::cout << "Created rational: " << r1 << std::endl;
	std::cout << "Trying to divide by <0/1>: \n";
	try {
		r1 /= 0;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	std::cout << std::endl;
}

void main()
{
	test_reference();

	//test_add();
	//test_sub();
	//test_mul();
	//test_div();

	//test_comparison();
	//test_signfunctions();

	//test_IO();

	//test_exception();
}


