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
	n1 = std::abs(n1);
	n2 = std::abs(n2);

	if (n1 == 0 || n2 == 0)
	{
		return 0;
	}

	// Subtract the lesser number from the greater number until equal (= either 0 or common divider)
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
	// Calculate common divider
	int gcd_value(gcd(numerator, denominator));

	// If there is a common divider between numerator and denominator, divide by it.
	if (gcd_value != 0)
	{
		numerator /= gcd_value;
		denominator /= gcd_value;
	}

	// Also, if the denominator is negative, flip the signs.
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
	// Calculate lowest common multiple and calculate "normalized" numerators (if they had the same denominators)
	int lcm_value(lcm(this->denominator, other.denominator));
	int num1(lcm_value / this->denominator * this->numerator);
	int num2(lcm_value / other.denominator * other.numerator);

	// Then compare and return the result
	if (num1 > num2)
	{
		return 1;
	}
	else if (num1 < num2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void rational_t::add(rational_t const& other)
{
	// Calc lowest common multiple between the two values
	int new_denominator(lcm(this->denominator, other.denominator));

	// Then convert the value to have the final denominator
	this->numerator *= new_denominator / this->denominator;
	this->denominator = new_denominator;

	// Then add the multiplied numerator of the other half.
	numerator += other.numerator * (new_denominator / other.denominator);

	// At the end, normalize it to get canonical form.
	normalize();
}
void rational_t::sub(rational_t const& other)
{
	// Just like in add(), first convert both numbers to have the same denominator, then substract them.
	int new_denominator(lcm(this->denominator, other.denominator));
	this->numerator *= new_denominator / this->denominator;
	this->denominator = new_denominator;

	numerator -= other.numerator * (new_denominator / other.denominator);
	normalize();
}
void rational_t::mul(rational_t const& other)
{
	// When multiplying to rationals, no previous conversion is needed.
	numerator *= other.numerator;
	denominator *= other.denominator;

	normalize();
}
void rational_t::div(rational_t const& other)
{
	// If denominator is 0, abort and throw an exception.
	if (!other.is_consistent())
	{
		throw divide_by_zero_exception();
	}

	rational_t tmp(other.denominator, other.numerator);
	mul(tmp);

	normalize();
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
	denominator = _denominator;

	// If not consistent (0 in denominator), display and throw an error/Exception.
	if (!is_consistent())
	{
		throw divide_by_zero_exception();
	}

	normalize();
}
rational_t::rational_t(rational_t const& src)
{
	numerator = src.numerator;
	denominator = src.denominator;
}

bool rational_t::is_positive()
{
	return numerator > 0;
}
bool rational_t::is_negative()
{
	return numerator < 0;
}
bool rational_t::is_zero()
{
	return numerator == 0;
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
	return "<" + (	numerator%denominator==0 ? 
					std::to_string(numerator/denominator) : 
					std::to_string(numerator) + "/" + std::to_string(denominator) ) + ">";
}
std::ostream& rational_t::print(std::ostream& out) const
{
	out << as_string();
	return out;
}
std::istream& rational_t::scan(std::istream& in)
{
	// read in two values from the designated stream
	// If reading in fails, set it to 1 or 0 respectively
	if (!(in >> this->numerator))
		this->numerator = 0;
	if (!(in >> this->denominator))
		this->denominator = 1;

	return in;
}

rational_t rational_t::operator=(rational_t const& src)
{
	// On assignment, check if the object is the same.
	if (*this == src)
	{
		return *this;
	}
	else
	{
		// If it is a different object assign the values directly instead of claiming new memory.
		this->numerator = src.numerator;
		this->denominator = src.denominator;
		return *this;
	}
}

// Delegate to add/sub/mul/div
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

// Delegate to cmp() function
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

// Non member functions
std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs)
{
	// Delegate to print
	rhs.print(lhs);
	return lhs;
}
std::istream& operator>>(std::istream& lhs, rational_t& rhs)
{
	// Delegate to scan
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
	return tmp - rhs;
}
rational_t operator*(int const lhs, rational_t& rhs)
{
	rational_t tmp(lhs);
	return tmp * rhs;
}
rational_t operator/(int const lhs, rational_t& rhs)
{
	rational_t tmp(lhs);
	return tmp / rhs;
}

rational_t operator+(rational_t& lhs, int const rhs)
{
	return operator+(rhs, lhs);
}
rational_t operator-(rational_t& lhs, int const rhs)
{
	rational_t tmp(rhs);
	return lhs - tmp;
}
rational_t operator*(rational_t& lhs, int const rhs)
{
	return operator*(rhs, lhs);
}
rational_t operator/(rational_t& lhs, int const rhs)
{
	rational_t tmp(rhs);
	return lhs / tmp;
}
