#include "rational_type.h"
#include "divide_by_zero_exception.h"
#include<string>

// private
int rational_t::lcm(int n1, int n2) const
{
	return (n1 * n2) / gcd(n1, n2);
}
int rational_t::gcd(int n1, int n2) const
{
	while (n1 != n2)
	{
		if (n1 > n2)
		{
			n1 -= n2;
		}
		else
		{
			n2 -= n1;
		}
	}

	return n1;
}
void rational_t::normalize()
{
	int gcd_value(gcd(numerator, denominator));
	if (gcd_value != 0)
	{
		numerator /= gcd_value;
		denominator /= gcd_value;
	}

	if (denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}
}
bool rational_t::is_consistent() const
{
	return this->denominator!=0;
}

int rational_t::cmp(rational_t const& other) const 
{
	int lcm_value(lcm(this->denominator, other.denominator));
	int factor1(lcm_value / this->denominator);
	int factor2(lcm_value / other.denominator);

	if (this->numerator * factor1 > other.numerator * factor2)
	{
		return 1;
	}
	else if (this->numerator * factor1 < other.numerator * factor2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

// public
rational_t::rational_t()
{
	numerator = 1;
	denominator = 1;
}
rational_t::rational_t(int const _numerator)
{
	numerator = _numerator;
	denominator = 1;
}
rational_t::rational_t(int const _numerator, int const _denominator)
{
	numerator = _numerator;

	if (denominator == 0)
	{
		throw divide_by_zero_exception();
	}

	denominator = _denominator;

	if (!is_consistent())
	{
		std::cout << "Warning: Invalid denominator. Setting default value.\n";
		denominator = 1;
	}
}
rational_t::rational_t(rational_t const& src)
{
	numerator = src.numerator;
	denominator = src.denominator;
}

void rational_t::add(rational_t const& other)
{
	numerator += other.numerator;
}
void rational_t::sub(rational_t const& other)
{
	numerator -= other.numerator;
}
void rational_t::mul(rational_t const& other)
{
	numerator *= other.numerator;
	denominator *= other.denominator;

	normalize();
}
void rational_t::div(rational_t const& other)
{
	numerator /= other.numerator;

	if (other.denominator == 0)
	{
		throw divide_by_zero_exception();
	}

	denominator /= other.denominator;

	normalize();
}

rational_t rational_t::operator=(rational_t const& src)
{
	if (*this == src)
	{
		return *this;
	}
	else
	{
		this->numerator = src.numerator;
		this->denominator = src.denominator;
		return *this;
	}
}

rational_t rational_t::operator+(rational_t const& other)
{
	rational_t tmp(*this);
	tmp.add(other);
	return tmp;
}
rational_t rational_t::operator-(rational_t const& other)
{
	rational_t tmp(*this);
	tmp.sub(other);
	return tmp;
}
rational_t rational_t::operator*(rational_t const& other)
{
	rational_t tmp(*this);
	tmp.mul(other);
	return tmp;
}
rational_t rational_t::operator/(rational_t const& other)
{
	rational_t tmp(*this);
	tmp.div(other);
	return tmp;
}

rational_t rational_t::operator+=(rational_t const& other)
{
	add(other);
	return *this;
}
rational_t rational_t::operator-=(rational_t const& other)
{
	sub(other);
	return *this;
}
rational_t rational_t::operator*=(rational_t const& other)
{
	mul(other);
	return *this;
}
rational_t rational_t::operator/=(rational_t const& other)
{
	div(other);
	return *this;
}

bool rational_t::operator==(rational_t const& other) const
{
	return cmp(other) == 0;
}
bool rational_t::operator!=(rational_t const& other) const
{
	return cmp(other) != 0;
}
bool rational_t::operator>(rational_t const& other) const
{
	return cmp(other) == 1;
}
bool rational_t::operator<(rational_t const& other) const
{
	return cmp(other) == -1;
}
bool rational_t::operator>=(rational_t const& other) const
{
	return cmp(other) != -1;
}
bool rational_t::operator<=(rational_t const& other) const
{
	return cmp(other) != 1;
}

std::ostream& operator<<(std::ostream& lhs, rational_t& rhs)
{
	rhs.print(lhs);
	return lhs;
}
std::istream& operator>>(std::istream& lhs, rational_t& rhs)
{
	rhs.scan(lhs);
	return lhs;
}

rational_t operator+(int const lhs, rational_t& rhs)
{
	rational_t tmp(lhs);
	return tmp + rhs;
}
rational_t operator-(int const lhs, rational_t& rhs)
{
	rational_t tmp(lhs);
	return tmp - lhs;
}
rational_t operator*(int const lhs, rational_t& rhs)
{
	rational_t tmp(lhs);
	return tmp * lhs;
}
rational_t operator/(int const lhs, rational_t& rhs)
{
	rational_t tmp(lhs);
	return tmp / lhs;
}

int rational_t::get_numerator() const
{
	return numerator;
}
int rational_t::get_denominator() const
{
	return denominator;
}

std::string rational_t::as_string() const
{
	return "<" + std::to_string(numerator) + "/" + std::to_string(denominator) + ">";
}
std::ostream& rational_t::print(std::ostream& out) const
{
	out << as_string();
	return out;
}
std::istream& rational_t::scan(std::istream& in)
{
	rational_t tmp;
	if (!(in >> tmp.numerator))
		tmp.numerator = 0;
	if (!(in >> tmp.denominator))
		tmp.denominator = 0;

	return in;
}

bool rational_t::is_positive()
{
	return numerator>0;
}
bool rational_t::is_negative()
{
	return numerator<0;
}
bool rational_t::is_zero()
{
	return numerator==0;
}