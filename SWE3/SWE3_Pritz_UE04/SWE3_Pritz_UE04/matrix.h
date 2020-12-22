#ifndef MATRIX_H
#define MATRIX_H
#include<vector>

template<typename T>
class Matrix {
	typedef T value_t;
	
private:
	value_t** elements;

	// Adds the value of another rational
	void add(Matrix<value_t> const& other)
	{
		elements[0][0] += other.elements[0][0];
	}
	// Subtracts the value of another rational
	void sub(Matrix<value_t> const& other)
	{
		elements[0][0] -= other.elements[0][0];
	}
	// Multiplies by the value of another rational
	void mul(Matrix<value_t> const& other)
	{
		elements[0][0] *= other.elements[0][0];
	}
	// Divides by the value of another rational
	void div(Matrix<value_t> const& other)
	{
		elements[0][0] /= other.elements[0][0];
	}

public:

	Matrix()
	{
		elements = new value_t*[1];
		elements[0] = new value_t[1];
		elements[0][0] = 1;
	}
	Matrix(T const& val)
	{
		elements = new value_t*[1];
		elements[0] = new value_t[1];
		elements[0][0] = val;
	}
	~Matrix()
	{
		delete[] elements[0];
		delete[] elements;
	}

	T get_element() const
	{
		return elements[0][0];
	} 

	Matrix<value_t> operator=(Matrix<value_t> const& other)
	{
		elements[0][0] = other.elements[0][0];
		return *this;
	}
	Matrix<value_t> operator+(Matrix<value_t> const& other)
	{
		Matrix<value_t> tmp(*this);
		tmp.add(other);
		return tmp;
	}
	// Subtract operator override.
	Matrix<value_t> operator-(Matrix<value_t> const& other)
	{
		Matrix<value_t> tmp(*this);
		tmp.sub(other);
		return tmp;
	}
	// Multiply operator override.
	Matrix<value_t> operator*(Matrix<value_t> const& other)
	{
		Matrix<value_t> tmp(*this);
		tmp.mul(other);
		return tmp;
	}
	// Divide operator override.
	Matrix<value_t> operator/(Matrix<value_t> const& other)
	{
		Matrix<value_t> tmp(*this);
		tmp.div(other);
		return tmp;
	}
	// Add assignment operator override.
	Matrix<value_t> operator+=(Matrix<value_t> const& other)
	{
		add(other);
		return *this;
	}
	// Subtract assignment operator override.
	Matrix<value_t> operator-=(Matrix<value_t> const& other)
	{
		sub(other);
		return *this;
	}
	// Multiply assignment operator override.
	Matrix<value_t> operator*=(Matrix<value_t> const& other)
	{
		mul(other);
		return *this;
	}
	// Divide assignment operator override.
	Matrix<value_t> operator/=(Matrix<value_t> const& other)
	{
		div(other);
		return *this;
	}

	// Equal operator override.
	bool operator==(Matrix<value_t> const& other) const
	{
		return elements[0][0] == other.elements[0][0];
	}
	
	// Unequal operator override
	bool operator!=(Matrix<value_t> const& other) const
	{
		return elements[0][0] != other.elements[0][0];
	}
	// Greater than operator override
	bool operator>(Matrix<value_t> const& other) const
	{
		return elements[0][0] > other.elements[0][0];
	}
	// Less than operator override
	bool operator<(Matrix<value_t> const& other) const
	{
		return elements[0][0] < other.elements[0][0];
	}
	// Greater or equal than operator override
	bool operator>=(Matrix<value_t> const& other) const
	{
		return elements[0][0] >= other.elements[0][0];
	}
	// Less or equal than operator override
	bool operator<=(Matrix<value_t> const& other) const
	{
		return elements[0][0] <= other.elements[0][0];
	}
};

#endif