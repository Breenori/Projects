#ifndef COMPLEX_TYPE_H
#define COMPLEX_TYPE_H

#include <iostream>
#include <string>
#include "operations.h"
#include "divide_by_zero.h"


template<typename T, typename S = ops::nelms_traits_t<T>>
class Complex {
private:

	typedef S traits_t;

	//Barton-Nackmann Trick (non-member operator inlining)
	friend Complex<T> operator+(Complex<T>& const lhs, Complex<T>& const rhs) {
		Complex<T> temp(rhs);
		temp.add(lhs);
		return temp;
	}
	friend Complex<T> operator-(Complex<T>& const lhs, Complex<T>& const rhs) {
		Complex<T> temp(lhs);
		temp.sub(rhs);
		return temp;
	}
	friend Complex<T> operator*(Complex<T>& const lhs, Complex<T>& const rhs) {
		Complex<T> temp(lhs);
		temp.mul(rhs);
		return temp;
	}
	friend Complex<T> operator/(Complex<T>& const lhs, Complex<T>& const rhs) {
		Complex<T> temp(lhs);
		temp.div(rhs);
		return temp;
	}
	friend Complex<T>& operator+=(Complex<T>& lhs, Complex<T>& const rhs) {		// Referenz zurückgeben
		lhs.add(rhs);
		return lhs;
	}
	friend Complex<T>& operator-=(Complex<T>& lhs, Complex<T>& const rhs) {		// Referenz zurückgeben
		lhs.sub(rhs);
		return lhs;
	}
	friend Complex<T>& operator*=(Complex<T>& lhs, Complex<T>& const rhs) {		// Referenz zurückgeben
		lhs.mul(rhs);
		return lhs;
	}
	friend Complex<T>& operator/=(Complex<T>& lhs, Complex<T>& const rhs) {		// Referenz zurückgeben
		lhs.div(rhs);
		return lhs;
	}

	T real;	//statt int wird nun T verwendet
	T imag;

	void print(std::ostream& o) const {
		// an traits class delegieren
		if (ops::is_negative(imag)) {
			o << real << " " << imag << "i\n";
		} else {
			o << real << " + " << imag << "i\n";
		}
	}

public:
	Complex() {	//Standardkonstruktor
		// use traits class to initialize
		real = traits_t::zero();
		imag = traits_t::zero();
	}

	Complex(T _real, T _imag) {	// Overloadkonstruktor, _ um zu differenzieren von den anderen Elementen
		real = _real;
		imag = _imag;
	}

	Complex(const Complex<T>& other) {	//Kopierkonstruktor, mit dem selben Datentypen wie das Objekt von welchen Kopiert wird
		real = other.real;
		imag = other.imag;
	}
	~Complex() {	//Destruktor
	}

	void add(Complex<T>& const other) {
		real = real + other.real;
		imag = imag + other.imag;
	}

	void sub(Complex<T>& const other) {
		real = real - other.real;
		imag = imag - other.imag;
	}
	void mul(Complex<T>& const other) {
		T t_real(real);
		T t_imag(imag);

		real = (t_real * other.real) - (t_imag * other.imag);
		imag = (t_real * other.imag) + (t_imag * other.real);
	}

	void div(Complex<T>& const other) {
		T t_real(real);
		T t_imag(imag);

		T num((other.real * other.real) + (other.imag * other.imag));

		if (ops::is_zero(num))
		{
			throw new DivideByZeroException();
		}
		// TODO: Throw Divide by Zero Exception

		real = ((t_real * other.real) + (t_imag * other.imag)) / num;
		imag = ((t_imag * other.real) - (t_real * other.imag)) / num;
	}

	std::string as_string() const {
		return ops::is_negative(imag) ?
			? std::to_string(real) + " " + std::to_string(imag) + 'i'
			: std::to_string(real) + " + " + std::to_string(imag) + 'i';
	}

};



#endif // !COMPLEX_TYPE_H