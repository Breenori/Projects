#ifndef OPERATIONS_H
#define OPERATIONS_H

#include<iostream>
using std::cout;

namespace ops {
	template<typename T>
	class nelms_traits_t {

	};

	template<>
	class nelms_traits_t<int> {
	public:
		typedef int value_t;

		static value_t one()
		{
			cout << "in ops::one<int>\n";
			return 1;
		}

		static value_t zero() {
			cout << "in ops::zero<int>\n";
			return 0;
		}
	};

	template<>
	class nelms_traits_t<double> {
	public:
		typedef int value_t;

		static value_t one()
		{
			cout << "in ops::one<int>\n";
			return 1.0;
		}

		static value_t zero() {
			cout << "in ops::zero<int>\n";
			return 0.0;
		}
	};

	template<typename T> bool is_negative(const T& a) {
		return a < nelms_traits_t<T>::zero();
	}

	template<typename T> bool is_zero(const T& a)
	{
		return a == nelms_traits_t<T>::zero();
	}

	template<typename T> T negate(const T& a)
	{
		return nelms_traits_t<T>::zero() - a;
	}
}

#endif