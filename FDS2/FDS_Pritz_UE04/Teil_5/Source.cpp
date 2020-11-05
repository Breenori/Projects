#include<iostream>
#include<string>
#include<vector>
using std::cout;
using std::vector;

// Function pointer
typedef double (*function_t) (double const);

// Returns the x-value of the zero value.
double bisection(function_t p_fun, double a, double b, double epsilon = 0.0001);
// First function of the sheet.
double f1(double const x);
// Second function of the sheet.
double f2(double const x);
// Third function of the sheet.
double f3(double const x);

// Returns the sign of a double value as int.
int sign(double d);

void test_f1();
void test_f2();
void test_f3();


void main()
{
	test_f1();
	//test_f2();
	//test_f3();
}

double bisection(function_t p_fun, double a, double b, double epsilon)
{
	// Calculate the middle (value)
	double m((a + b) / 2);
	double fm = p_fun(m);

	// If the interval spacing is below epsilon or middle value is zero, the right x has been found.
	if ((b - a) < epsilon || fm == 0)
	{
		return m;
	}
	else
	{
		double fa = p_fun(a);

		// If signs differ between fa and fm, go left. Else, go right.
		// this means, if we dont find differing signs, we will always go right and end up with m =~ b;
		if (sign(fa) != sign(fm))
		{
			return bisection(p_fun, a, m);
		}
		else
		{
			return bisection(p_fun, m, b);
		}
	}
}

double f1(double const x)
{
	return 2 * pow(x, 3) - 3 * pow(x, 2) + (1/2.0f);
}
double f2(double const x)
{
	return x + exp(x);
}
double f3(double const x)
{
	double a = (5 / 2) * pow(x, 2);
	return (5/2.0f)*pow(x,2) - 7*x + 4;
}

int sign(double d)
{
	return d < 0 ? -1 : 1;
}

void test_f1()
{
	cout << bisection(f1, -2, 0) << std::endl;
	cout << bisection(f1, -2, 4) << std::endl;
}
void test_f2()
{
	cout << bisection(f2, -1, 1) << std::endl;
	cout << bisection(f2, 0, 1) << std::endl;
}
void test_f3()
{
	cout << bisection(f3, -1, 4) << std::endl;
	cout << bisection(f3, 1, 4) << std::endl;
	cout << bisection(f3, -1, 1) << std::endl;
}
