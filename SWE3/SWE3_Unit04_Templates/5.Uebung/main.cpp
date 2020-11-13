#include "complex_type.h"

template<typename T>	//dieser template Parameter S hat mit dem Template von Complex nichts zu tun
void print_result(Complex<T>& const co) {
	std::cout << co.as_string() << std::endl;
}

void test_addition() {
	Complex<int> a(3, 7);	// (implizit -> wir haben nicht spezifiziert das es eine Klasse Complex<int> gibt) Template spezialisierung
	Complex<int> b(-5, -6);
	a.add(b);
	print_result<int>(a);	//hier kann/muss nun auch spezialisiert werden
}

void test_addition_double() {
	Complex<double> a(3.0, 7.0);
	Complex<double> b(-5.4, -6.4);
	a.add(b);
	print_result<double>(a);	//hier kann/muss nun auch spezialisiert werden
}

void test_addition_operator() {
	Complex<int> a(3, 7);
	Complex<int> b(-5, -6);
	Complex<int> c(a + b);
	print_result<int>(c);
}

void test_substaction_operator() {
	Complex<int> a(3, 7);
	Complex<int> b(-5, -6);
	Complex<int> c(a - b);
	print_result<int>(c);
}

void test_multiplication_operator() {
	Complex<int> a(3, 7);
	Complex<int> b(-5, -6);
	Complex<int> c(a * b);
	print_result<int>(c);
}

void test_division_operator() {
	Complex<int> a(3, 7);
	Complex<int> b(-5, -6);
	Complex<int> c(a / b);
	print_result<int>(c);
}

void test_add_equal_operator() {
	Complex<double> a(3.0, 7.0);
	Complex<double> b(-5.4, -6.4);
	a = a + b;
	print_result<double>(a);
}

void test_initialize()
{
	Complex<int> a;
	print_result(a);
}

void main() {
	std::cout << "Testing complex<T> number operations:\n";
	test_addition();
	test_addition_double();
	test_addition_operator();
	test_substaction_operator();
	test_multiplication_operator();
	test_division_operator();
	test_add_equal_operator();
	test_initialize();
}