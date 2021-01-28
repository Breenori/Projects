#include<iostream>
using std::cout;

// returns whether a number is prime or not
bool is_prime(int const num);
// Wrapper for the recursive function is_prime()
bool is_prime_wrapper(int const num, int const currdiv);

void main()
{
	for (int i(0); i < 50; i++)
	{
		if (is_prime(i))
		{
			cout << i << " is prime!" << std::endl;
		}
		else
		{
			//cout << i << " is not prime!" << std::endl;
		}
	}
	
}

bool is_prime(int const num)
{
	if (num < 0)
	{
		cout << "Negative number. Prime numbers are restricted to natural numbers." << std::endl;
		return false;
	}

	// If 0, 1 or any even number that isn't two, return false.
	if (num == 0 || num == 1 || num != 2 && num % 2 == 0)
	{
		return false;
	}
	// For all other odd numbers, do the recursive check.
	else
	{
		return is_prime_wrapper(num, 3);
	}
}
bool is_prime_wrapper(int const num, int const currdiv)
{
	// If we have checked every number from 2 to sqrt(num) we can stop and return true.
	if (currdiv > std::sqrt(num))
	{
		return true;
	}
	// If the divisor is a prime number and divides the given number, it is not prime.
	else if (is_prime(currdiv) && num % currdiv == 0)
	{
		return false;
	}
	// If there'S still numbers below sqrt(num) remaining, we check the next one.
	else
	{
		return is_prime_wrapper(num, currdiv + 2);
	}
}