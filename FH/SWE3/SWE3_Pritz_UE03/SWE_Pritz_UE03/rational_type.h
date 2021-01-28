#ifndef RATIONAL_TYPE_H
#define RATIONAL_TYPE_H
#include<iostream>


class rational_t {

	// Friend declarations

	friend std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs);
	friend std::istream& operator>>(std::istream& lhs, rational_t& rhs);
	friend rational_t operator+(int const lhs, rational_t& rhs);
	friend rational_t operator-(int const lhs, rational_t& rhs);
	friend rational_t operator*(int const lhs, rational_t& rhs);
	friend rational_t operator/(int const lhs, rational_t& rhs);
	friend rational_t operator+(rational_t& lhs, int const rhs);
	friend rational_t operator-(rational_t& lhs, int const rhs);
	friend rational_t operator*(rational_t& lhs, int const rhs);
	friend rational_t operator/(rational_t& lhs, int const rhs);

private:
	int numerator;
	int denominator;

	// Returns the "least common multiplier" of two numbers
	int lcm(int n1, int n2) const;
	// Returns the "greatest common divider" of two numbers
	int gcd(int n1, int n2) const;
	// Transforms the current rational into it's canonical representation
	void normalize();
	// Returns whether this rational is in a consistent state
	bool is_consistent() const;

	// Compares two rationals.
	// Returns 0 if equal, -1 if main rational is less and +1 if main rational is greater.
	int cmp(rational_t const& other) const;

	// Adds the value of another rational
	void add(rational_t const& other);
	// Subtracts the value of another rational
	void sub(rational_t const& other);
	// Multiplies by the value of another rational
	void mul(rational_t const& other);
	// Divides by the value of another rational
	void div(rational_t const& other);

	// Prints the current rational to the designated outputstream
	std::ostream& print(std::ostream& out = std::cout) const;
	// Reads in a rational from the given inputstream
	std::istream& scan(std::istream& in);

public:
	// Creates a rational <1/1>
	rational_t();
	// Creates a rational <numerator/1>
	rational_t(int const _numerator);
	// Creates a rational <numerator, denominator>
	rational_t(int const _numerator, int const _denominator);
	// Creates a rational using another rational
	rational_t(rational_t const& src);
	
	// Assignment operator override.
	rational_t operator=(rational_t const& src);

	// Add operator override.
	rational_t operator+(rational_t const& other);
	// Subtract operator override.
	rational_t operator-(rational_t const& other);
	// Multiply operator override.
	rational_t operator*(rational_t const& other);
	// Divide operator override.
	rational_t operator/(rational_t const& other);

	// Add assignment operator override.
	rational_t operator+=(rational_t const& other);
	// Subtract assignment operator override.
	rational_t operator-=(rational_t const& other);
	// Multiply assignment operator override.
	rational_t operator*=(rational_t const& other);
	// Divide assignment operator override.
	rational_t operator/=(rational_t const& other);

	// Equal operator override.
	bool operator==(rational_t const& other) const;
	// Unequal operator override
	bool operator!=(rational_t const& other) const;
	// Greater than operator override
	bool operator>(rational_t const& other) const;
	// Less than operator override
	bool operator<(rational_t const& other) const;
	// Greater or equal than operator override
	bool operator>=(rational_t const& other) const;
	// Less or equal than operator override
	bool operator<=(rational_t const& other) const;

	// Returns the numerator of the current rational
	int get_numerator() const;
	// Returns the denominator of the current rational
	int get_denominator() const;

	// Returns the current rational as string as <numerator/denominator>
	std::string as_string() const;

	// Returns whether the rational is positive or not
	bool is_positive();
	// Returns whether the rational is negative or not
	bool is_negative();
	// Returns whether the rational is zero or not
	bool is_zero();
};

// Non member operators

// Output operator overide
std::ostream& operator<<(std::ostream& lhs, rational_t const& rhs);
// Input operator override
std::istream& operator>>(std::istream& lhs, rational_t& rhs);

// Add operator override. Combination with int.
rational_t operator+(int const lhs, rational_t& rhs);
// Subtract operator override. Combination with int.
rational_t operator-(int const lhs, rational_t& rhs);
// Multiply operator override. Combination with int.
rational_t operator*(int const lhs, rational_t& rhs);
// Divide operator override. Combination with int.
rational_t operator/(int const lhs, rational_t& rhs);
// Add operator override. Combination with int.
rational_t operator+(rational_t& lhs, int const rhs);
// Subtract operator override. Combination with int.
rational_t operator-(rational_t& lhs, int const rhs);
// Multiply operator override. Combination with int.
rational_t operator*(rational_t& lhs, int const rhs);
// Divide operator override. Combination with int.
rational_t operator/(rational_t& lhs, int const rhs);


#endif
