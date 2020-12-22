#include<iostream>
#include "analysis_traits.h"
using std::cout;

/* Variant 1: without traits classes
template<typename T>
void describe(T const& value)
{
	// if value is int type return int max
	// if value is double type return double max
}

template<>
void describe<int>(const int& value) {
	cout << "min val of value:" << INT_MIN << "\n";
	cout << "min val of value:" << INT_MAX << "\n";
	cout << "negative val of value " << value * -1 << "\n";
	cout << "zero element: " << 0 << "\n";
	cout << "one element: " << 1 << "\n";
}

template<>
void describe<double>(const double& value) {
	cout << "min val of value:" << DBL_MIN << "\n";
	cout << "min val of value:" << DBL_MAX << "\n";
	cout << "negative val of value " << value * -1.0 << "\n";
	cout << "zero element: " << 0.0 << "\n";
	cout << "one element: " << 1.0 << "\n";
}*/
template<typename T>
void describe(T const& value)
{
	T min = analysis::analysis_trait<T>::min();
	T max = analysis::analysis_trait<T>::max();
	T neg = analysis::analysis_trait<T>::neg(value);
	T zero = analysis::analysis_trait<T>::zero();
	T one = analysis::analysis_trait<T>::one();

	cout << "min val of value:" << min << "\n";
	cout << "min val of value:" << max << "\n";
	cout << "negative val of value " << neg << "\n";
	cout << "zero element: " << zero << "\n";
	cout << "one element: " << one << "\n";

	cout << analysis::analysis_trait<T>::as_string(value);
}

int main()
{
	cout << "use int analyze traits class\n";

	// template spezialisierung
	describe(42);
	cout << "-------------------------------------\n";
	cout << "use double analyze traits class\n";
	describe(42.42);
	cout << "-------------------------------------\n";
	cout << "use string analyze traits class\n";
	describe<std::string>("hello");
	return 0;
}