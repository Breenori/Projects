#include "complex_type.h"
#include "divide_by_zero_exception.h"
using std::cout;
using std::string;
using std::ostream;

Complex::Complex()
{
	real = 0;
	imag = 0;
}

Complex::Complex(int const _real, int const _imag)
{
	real = _real;
	imag = _imag;
}

Complex::Complex(Complex const& other) // Copy Constructor
{
	real = other.real;
	imag = other.imag;
}


string Complex::as_string() const
{
	return imag < 0 ?	std::to_string(real) + " " + std::to_string(imag) + "i" :
						std::to_string(real) + " +" + std::to_string(imag) + "i";
}

void Complex::print(ostream& os) const
{
	if (imag < 0)
	{
		os << real << " " << imag << 'i' << std::endl;
	}
	else
	{
		os << real << " +" << imag << 'i' << std::endl;
	}
}

void Complex::add(Complex const& other)
{
	real += other.real;
	imag += other.imag;
}

void Complex::sub(Complex const& other)
{
	real -= other.real;
	imag -= other.imag;
}

void Complex::mul(Complex const& other)
{
	int t_real = real;
	int t_imag = imag;

	real = t_real * other.real - t_imag * other.imag;
	imag = t_real * other.imag + t_imag * other.real;
}

void Complex::div(Complex const& other)
{
	int t_real = real;
	int t_imag = imag;

	int num = (std::pow(other.real, 2) + std::pow(other.imag, 2));

	if (num == 0)
	{
		throw DivideByZeroException();
	}

	real = (t_real * other.real + t_imag * other.imag) / num;
	imag = (t_imag * other.real - t_real * other.imag) / num;
}

// operator overloads
Complex Complex::operator+(Complex const& other)
{
	Complex tmp(*this);
	tmp.add(other);	// Delegate
	return tmp;
}

Complex Complex::operator-(Complex const& other)
{
	Complex tmp(*this);
	tmp.sub(other);	// Delegate
	return tmp;
}

Complex Complex::operator*(Complex const& other)
{
	Complex tmp(*this);
	tmp.mul(other);	// Delegate
	return tmp;
}

Complex Complex::operator/(Complex const& other)
{
	Complex tmp(*this);
	tmp.div(other);	// Delegate
	return tmp;
}

Complex& Complex::operator+=(Complex const& other)
{
	add(other);
	return *this;
}

Complex& Complex::operator-=(Complex const& other)
{
	sub(other);
	return *this;
}

Complex& Complex::operator*=(Complex const& other)
{
	mul(other);
	return *this;
}

Complex& operator/=(Complex& lhs, Complex& rhs)
{
	lhs.div(rhs);
	return lhs;
}

ostream& operator<<(ostream& lhs, Complex const& rhs)
{
	rhs.print(lhs);
	return lhs;
}