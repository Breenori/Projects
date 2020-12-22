#ifndef OPERATIONS_H
#define OPERATIONS_H

#include<iostream>
#include<string>
#include "matrix.h"
using std::cout;

namespace ops {
	template<typename T>
	class nelms_traits_t {
		static std::string to_string(T const& var)
		{
			return std::to_string(var);
		}
	};

	template<>
	class nelms_traits_t<int> {
	public:
		typedef int value_t;

		static value_t one()
		{
			return 1;
		}

		static value_t zero() {
			return 0;
		}

		static std::string to_string(value_t const& var)
		{
			return std::to_string(var);
		}
	};

	template<>
	class nelms_traits_t<double> {
	public:
		typedef int value_t;

		static value_t one()
		{
			return 1.0;
		}

		static value_t zero() {
			return 0.0;
		}

		static std::string to_string(value_t const& var)
		{
			return std::to_string(var);
		}
	};

	template<>
	class nelms_traits_t<Matrix<int>> {
	public:
		typedef Matrix<int> value_t;

		static value_t one()
		{
			return 1;
		}

		static value_t zero() {
			return 0;
		}

		static std::string to_string(Matrix<int> const& var)
		{
			return std::to_string(var.get_element());
		}
		
	};

	template<typename T> std::string to_string(T const& var)
	{
		return nelms_traits_t<T>::to_string(var);
	}

	template<typename T> bool is_negative(T const& a)
	{
		return a < nelms_traits_t<T>::zero();
	}

	
	template<typename T> bool is_zero(T const& a)
	{
		return a == nelms_traits_t<T>::zero();
	}



	template<typename T> T negate(T const& a)
	{
		return nelms_traits_t<T>::zero() - a;
	}


	
	template<typename T> T abs(T const& a)
	{
		return is_negative(a) ? negate(a) : a;
	}


	template<typename T> T gcd(T n1, T n2)
	{
		n1 = abs(n1);
		n2 = abs(n2);

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
	
	// Returns the "least common multiplier" of two numbers
	template<typename T> T lcm(T n1, T n2)
	{
		return (n1 * n2) / gcd(n1, n2);
	}

	template<typename T> bool equals(T const& a, T const& b)
	{
		return a == b;
	}

	template<typename T> T remainder(T const& a, T const& b)
	{
		return a - (a / b);
	}
	
	template<typename T> bool divides(T const& a, T const& b)
	{
		return is_zero(remainder(a, b));
	}

	
}

#endif