#ifndef RATIONAL_TYPE_H
#define RATIONAL_TYPE_H
#include<iostream>


class rational_t {

	friend std::ostream& operator<<(std::ostream& lhs, rational_t& rhs);
	friend std::istream& operator>>(std::istream& lhs, rational_t& rhs);

private:
	int numerator;
	int denominator;

	int lcm(int n1, int n2) const;
	int gcd(int n1, int n2) const;
	void normalize();
	bool is_consistent() const;
	int cmp(rational_t const& other) const;

public:
	rational_t();
	rational_t(int const _numerator);
	rational_t(int const _numerator, int const _denominator);
	rational_t(rational_t const& src);
	rational_t operator=(rational_t const& src);

	void add(rational_t const& other);
	void sub(rational_t const& other);
	void mul(rational_t const& other);
	void div(rational_t const& other);

	rational_t operator+(rational_t const& other);
	rational_t operator-(rational_t const& other);
	rational_t operator*(rational_t const& other);
	rational_t operator/(rational_t const& other);

	rational_t operator+=(rational_t const& other);
	rational_t operator-=(rational_t const& other);
	rational_t operator*=(rational_t const& other);
	rational_t operator/=(rational_t const& other);

	bool operator==(rational_t const& other) const;
	bool operator!=(rational_t const& other) const;
	bool operator>(rational_t const& other) const;
	bool operator<(rational_t const& other) const;
	bool operator>=(rational_t const& other) const;
	bool operator<=(rational_t const& other) const;

	int get_numerator() const;
	int get_denominator() const;

	std::string as_string() const;
	std::ostream& print(std::ostream& out = std::cout) const;
	std::istream& scan(std::istream& in);

	bool is_positive();
	bool is_negative();
	bool is_zero();
};

std::ostream& operator<<(std::ostream& lhs, rational_t& rhs);
std::istream& operator>>(std::istream& lhs, rational_t& rhs);
rational_t operator+(int const lhs, rational_t& rhs);
rational_t operator-(int const lhs, rational_t& rhs);
rational_t operator*(int const lhs, rational_t& rhs);
rational_t operator/(int const lhs, rational_t& rhs);


#endif
