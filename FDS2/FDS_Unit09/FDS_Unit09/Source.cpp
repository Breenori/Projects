#include "pfc-mini.hpp"
#include<iostream>



int fib(int n)
{
	if (n <= 2)
	{
		return 1;
	}
	else {
		return fib(n - 1) + fib(n - 2);
	}
}

void do_sth()
{
	long l = fib(36);
}

void main()
{
	std::cout << pfc::in_s(pfc::timed_run(do_sth));
}