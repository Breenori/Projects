#include "point.h"
#include "operations.h"

void main()
{
	Point<double> a(42.0, 21.0);
	Point<int> b(21, 21);

	// implicit specialization of operations template
	cout << operations::abs<int>(-24) << std::endl;
	cout << operations::abs<double>(-24.0) << std::endl;

	operations::negate(a);
}