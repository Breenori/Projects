#include<functional>
#include<iostream>


int fibonacci(int n)
{
	if (n == 1)
	{
		return 1;
	}
	else if (n == 2)
	{
		return 1;
	}
	else
	{
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}

void main()
{
	for (int n(1); n < 100; n++)
	{
		std::cout << "fib von " << n << ": " << fibonacci(n) << std::endl;
	}
}