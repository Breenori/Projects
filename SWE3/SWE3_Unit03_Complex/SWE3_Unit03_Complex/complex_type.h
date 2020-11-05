#ifndef complex_type_h
#define complex_type_h
#include<iostream>
#include<string>

class Complex {

	// Friend declarations
	friend std::ostream& operator<<(std::ostream& lhs, Complex const& rhs);

private:
	int real;
	int imag;

	void print(std::ostream& o = std::cout) const;

public:
	Complex();
	Complex(int const _imag, int const _real);
	Complex(Complex const& other);

	void add(Complex const& other);
	void sub(Complex const& other);
	void mul(Complex const& other);
	void div(Complex const& other);
	std::string as_string() const;

	// Operator overloads
	Complex operator+(Complex const& other);
	Complex operator-(Complex const& other);
	Complex operator*(Complex const& other);
	Complex operator/(Complex const& other);

	Complex& operator+=(Complex const& other);
	Complex& operator-=(Complex const& other);
	Complex& operator*=(Complex const& other);

// Only visible in children classes and members (inheritage)
//protected:

};

// Version 2: Non class member operator
Complex& operator/=(Complex& lhs, Complex& rhs);
std::ostream& operator<<(std::ostream& lhs, Complex const& rhs);



#endif