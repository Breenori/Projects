#include "complex_type.h"
#include "divide_by_zero_exception.h"
using std::cout;
using std::exception;

void print_result(Complex const& co)
{
	//cout << co.as_string() << std::endl;
	// Now using operator<< with friend declaration:
	cout << co << "\n";
}

void test_addition()
{
	Complex a(3, 7);
	Complex b(-5, -6);
	a.add(b);
	print_result(a);
}

void test_subtraction()
{
	Complex a(3, 7);
	Complex b(5, -6);
	a.sub(b);
	print_result(a);
}

void test_multiplication()
{
	Complex a(5, -2);
	Complex b(3, 4);
	a.mul(b);
	print_result(a);
}

void test_division()
{
	Complex a(2, 1);
	Complex b(1, -2);
	a.div(b);
	print_result(a);
}

void test_add_operator()
{
	Complex a(3, 7);
	Complex b(-5, -6);
	Complex c = a + b;
	print_result(c);
}
void test_sub_operator()
{
	Complex a(3, 7);
	Complex b(5, -6);
	Complex c = a - b;
	print_result(c);
}
void test_mul_operator()
{
	Complex a(5, -2);
	Complex b(3, 4);
	Complex c = a * b;
	print_result(c);
}
void test_div_operator()
{
	Complex a(2, 1);
	Complex b(1, -2);
	Complex c = a / b;
	print_result(c);
}

void test_add_ass_operator()
{
	Complex a(3, 7);
	Complex b(-5, -6);
	a += b;
	print_result(a);
}
void test_sub_ass_operator()
{
	Complex a(3, 7);
	Complex b(5, -6);
	a -= b;
	print_result(a);
}
void test_mul_ass_operator()
{
	Complex a(5, -2);
	Complex b(3, 4);
	a *= b;
	print_result(a);
}
void test_div_ass_operator()
{
	Complex a(2, 1);
	Complex b(1, -2);
	a /= b;
	print_result(a);
}

void test_div_by_zero()
{
	Complex a(0, 0);
	Complex b(0, 0);
	try
	{
		Complex c = a / b;
		print_result(c);
	}
	catch (exception& e)
	{
		cout << e.what() << "\n";
	}
}

void main()
{
	cout << "Testing complex number operations: \n";
	//test_addition();
	//test_subtraction();
	//test_multiplication();
	//test_division();
	//test_add_operator();
	//test_sub_operator();
	//test_mul_operator();
	//test_div_operator();

	test_div_by_zero();
}