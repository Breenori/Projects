#include<iostream>
#include<string>

/*typedef double value_t;
typedef value_t (*function_t)(value_t, value_t);

value_t apply(value_t d1, value_t d2, function_t f)
{
	return f(d1, d2);
}

value_t add(value_t d1, value_t d2)
{
	return d1 + d2;
}

value_t multiply(value_t d1, value_t d2)
{
	return d1 * d2;
}*/

void bin(int const a)
{
	if (a > 1)
	{
		bin(a / 2);
		
	}

	std::cout << a % 2;
}

int binomcoeff(int n, int k)
{
	if (k > n)
	{
		return 0;
	}
	else if (k == 0 || k == n)
	{
		return 1;
	}
	else
	{
		return binomcoeff(n - 1, k - 1) + binomcoeff(n - 1, k);
	}
}

typedef double (*unary_function) (double);
double bisection(unary_function f, double a, double b, double epsilon = 0.0001)
{
	double h((a+b)/2);
	if ((b - a) < epsilon)
	{
		return h;
	}
	else
	{
		double f_a(f(a));
		double f_h(f(h));

		/*if (sign(f_h) != sign(f_a))
		{
			bisection(f, a, h);
		}
		else
		{
			bisection(f, h, b);
		}*/
	}
}

void main()
{
	//bin(1);

	for (int n(0); n < 30; n++)
	{
		for (int k(0); k <= n; k++)
		{
			std::cout << binomcoeff(n, k) << " ";
		}
		std::cout << "\n";
	}
}