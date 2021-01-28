#ifndef RATIONAL_TYPE_H
#define RATIONAL_TYPE_H
#include<iostream>
#include "operations.h"
#include "divide_by_zero_exception.h"
#include<string>
#include "matrix.h"

template<typename T = int, typename S = ops::nelms_traits_t<T>>
class rational_t {

	typedef T value_t;
	typedef S traits_t;

	// Friend declarations - barton nackman trick (inline)
	friend std::ostream& operator<<(std::ostream& lhs, rational_t<value_t> const& rhs)
	{
		// Delegate to print
		rhs.print(lhs);
		return lhs;
	}
	friend std::istream& operator>>(std::istream& lhs, rational_t<value_t>& rhs)
	{
		// Delegate to scan
		rhs.scan(lhs);
		return lhs;
	}
	friend rational_t<value_t> operator+(T const lhs, rational_t<value_t>& rhs)
	{
		rational_t<value_t> tmp(lhs);
		return tmp + rhs;
	}
	friend rational_t<value_t> operator-(T const lhs, rational_t<value_t>& rhs)
	{
		rational_t<value_t> tmp(lhs);
		return tmp - rhs;
	}
	friend rational_t<value_t> operator*(T const lhs, rational_t<value_t>& rhs)
	{
		rational_t<value_t> tmp(lhs);
		return tmp * rhs;
	}
	friend rational_t<value_t> operator/(T const lhs, rational_t<value_t>& rhs)
	{
		rational_t<value_t> tmp(lhs);
		return tmp / rhs;
	}
	friend rational_t<value_t> operator+(rational_t<value_t>& lhs, T const rhs)
	{
		rational_t<value_t> tmp(rhs);
		return tmp + lhs;
	}
	friend rational_t<value_t> operator-(rational_t<value_t>& lhs, T const rhs)
	{
		rational_t<value_t> tmp(rhs);
		return lhs - tmp;
	}
	friend rational_t<value_t> operator*(rational_t<value_t>& lhs, T const rhs)
	{
		rational_t<value_t> tmp(rhs);
		return tmp * lhs;
	}
	friend rational_t<value_t> operator/(rational_t<value_t>& lhs, T const rhs)
	{
		rational_t<value_t> tmp(rhs);
		return lhs / tmp;
	}

private:
	value_t numerator;
	value_t denominator;

	
	// Transforms the current rational into it's canonical representation
	void normalize()
	{
		// Calculate common divider
		value_t gcd_value(ops::gcd(numerator, denominator));

		// If there is a common divider between numerator and denominator, divide by it.
		if (gcd_value != traits_t::zero())
		{
			numerator /= gcd_value;
			denominator /= gcd_value;
		}

		// Also, if the denominator is negative, flip the signs.
		if (denominator < 0)
		{
			numerator *= ops::negate(traits_t::one());
			denominator *= ops::negate(traits_t::one());
		}
	}
	// Returns whether this rational is in a consistent state
	bool is_consistent() const
	{
		return !ops::is_zero(get_denominator());
	}


	// Compares two rationals.
	// Returns 0 if equal, -1 if main rational is less and +1 if main rational is greater.
	int cmp(rational_t<value_t> const& other) const
	{
		// Calculate lowest common multiple and calculate "normalized" numerators (if they had the same denominators)
		value_t lcm_value(ops::lcm(this->denominator, other.denominator));
		value_t num1(lcm_value / this->denominator * this->numerator);
		value_t num2(lcm_value / other.denominator * other.numerator);

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

	// Adds the value of another rational
	void add(rational_t<value_t> const& other)
	{
		// Calc lowest common multiple between the two values
		value_t new_denominator(ops::lcm(get_denominator(), other.get_denominator()));

		// Then convert the value to have the final denominator
		this->numerator *= new_denominator / get_denominator();
		this->denominator = new_denominator;

		// Then add the multiplied numerator of the other half.
		numerator += other.get_numerator() * (new_denominator / other.get_denominator());

		// At the end, normalize it to get canonical form.
		normalize();
	}
	// Subtracts the value of another rational
	void sub(rational_t<value_t> const& other)
	{
		// Just like in add(), first convert both numbers to have the same denominator, then substract them.
		value_t new_denominator(lcm(get_denominator(), other.get_denominator()));
		this->numerator *= new_denominator / this->denominator;
		this->denominator = new_denominator;

		numerator -= other.numerator * (new_denominator / other.denominator);
		normalize();
	}
	// Multiplies by the value of another rational
	void mul(rational_t<value_t> const& other)
	{
		// When multiplying to rationals, no previous conversion is needed.
		numerator *= other.get_numerator();
		denominator *= other.get_denominator();

		normalize();
	}
	// Divides by the value of another rational
	void div(rational_t<value_t> const& other)
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
	// Prints the current rational to the designated outputstream
	std::ostream& print(std::ostream& out = std::cout) const
	{
		out << as_string();
		return out;
	}
	// Reads in a rational from the given inputstream
	std::istream& scan(std::istream& in)
	{
		// read in two values from the designated stream
		// If reading in fails, set it to 1 or 0 respectively
		if (!(in >> this->numerator))
			this->numerator = traits_t::zero;
		if (!(in >> this->denominator))
			this->denominator = traits_t::one;

		return in;
	}	

public:
	// Creates a rational using default values for "one".
	rational_t()
	{
		numerator = traits_t::one();
		denominator = traits_t::one();
	}
	// Creates a rational <numerator/one>
	rational_t(T const& _numerator)
	{
		numerator = _numerator;
		denominator = traits_t::one();
	}
	// Creates a rational <numerator, denominator>
	rational_t(T const& _numerator, T const& _denominator)
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
	// Creates a rational using another rational
	rational_t(rational_t<value_t> const& src)
	{
		numerator = src.numerator;
		denominator = src.denominator;
	}


	// Assignment operator override.
	rational_t<value_t> operator=(rational_t<value_t> const& src)
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

	// Add operator override.
	rational_t<value_t> operator+(rational_t<value_t> const& other)
	{
		rational_t tmp(*this);
		tmp.add(other);
		return tmp;
	}
	// Subtract operator override.
	rational_t<value_t> operator-(rational_t<value_t> const& other)
	{
		rational_t tmp(*this);
		tmp.sub(other);
		return tmp;
	}
	// Multiply operator override.
	rational_t<value_t> operator*(rational_t<value_t> const& other)
	{
		rational_t tmp(*this);
		tmp.mul(other);
		return tmp;
	}
	// Divide operator override.
	rational_t<value_t> operator/(rational_t<value_t> const& other)
	{
		rational_t tmp(*this);
		tmp.div(other);
		return tmp;
	}

	// Add assignment operator override.
	rational_t<value_t> operator+=(rational_t<value_t> const& other)
	{
		add(other);
		return *this;
	}
	// Subtract assignment operator override.
	rational_t<value_t> operator-=(rational_t<value_t> const& other)
	{
		sub(other);
		return *this;
	}
	// Multiply assignment operator override.
	rational_t<value_t> operator*=(rational_t<value_t> const& other)
	{
		mul(other);
		return *this;
	}
	// Divide assignment operator override.
	rational_t<value_t> operator/=(rational_t<value_t> const& other)
	{
		div(other);
		return *this;
	}

	// Equal operator override.
	bool operator==(rational_t<value_t> const& other) const
	{
		return cmp(other) == 0;
	}
	// Unequal operator override
	bool operator!=(rational_t<value_t> const& other) const
	{
		return cmp(other) != 0;
	}
	// Greater than operator override
	bool operator>(rational_t<value_t> const& other) const
	{
		return cmp(other) == 1;
	}
	// Less than operator override
	bool operator<(rational_t<value_t> const& other) const
	{
		return cmp(other) == -1;
	}
	// Greater or equal than operator override
	bool operator>=(rational_t<value_t> const& other) const
	{
		return cmp(other) != -1;
	}
	// Less or equal than operator override
	bool operator<=(rational_t<value_t> const& other) const
	{
		return cmp(other) != 1;
	}

	// Returns the numerator of the current rational
	value_t get_numerator() const
	{
		return numerator;
	}
	
	// Returns the denominator of the current rational
	value_t get_denominator() const
	{
		return denominator;
	}

	// Returns the current rational as string as <numerator/denominator>
	std::string as_string() const
	{
		return "<" + ops::to_string(get_numerator()) + "/" + ops::to_string(get_denominator()) + ">";
	}

	

	// Returns whether the rational is positive or not
	bool is_positive()
	{
		return !(ops::is_negative(get_numerator()) || ops::is_zero(get_denominator()));
	}
	// Returns whether the rational is negative or not
	bool is_negative()
	{
		return ops::is_negative(get_numerator());
	}
	// Returns whether the rational is zero or not
	bool is_zero()
	{
		return ops::is_zero(get_numerator());
	}

	// Swaps numerator and denominator.
	void inverse()
	{
		value_t tmp = numerator;
		numerator = denominator;
		denominator = tmp;
	}
};

#endif
