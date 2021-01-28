#include "pfc-mini.hpp"
#include<iostream>
#include<fstream>
#include<locale>

// Since we can't modify the value of N for fibonacci with parameters or static values, we need to define it globally. Dirty, but necessary.
// ...due to pfc::timed_run() only accepting void and parameterless 
size_t TIMER_N(1);

// Returns the value for the fibonacci function at index <n>
size_t fibonacci(int n);
// Calls fibonacci with <TIMER_N>.
// Without parameters, to be callable by pfc::timed_run()
void fib_timed();

void main()
{
	// Write the output to a file, to display it as an excel chart.
	std::ofstream out("fib.csv");

	// Imbue the output to swap "." with "," for comma values to display it properly in excel.
	std::cout.imbue(std::locale("de"));
	out.imbue(std::locale("de"));
	
	// fibonacci(0);
	fibonacci(3501);

	// Start pfc once to avoid higher measured times for first N in debug mode
	//std::cout << pfc::in_s(pfc::timed_run(fib_timed)) << " (Coldstart)" << std::endl;

	// Test fibonacci runtime for the values 1 to 50.
	for (int i(1); i <= 50; i++)
	{
		double runtime = pfc::in_s(pfc::timed_run(fib_timed));
		// std::fixed needs to be used to avoid scientific notation for excel use (ex 0,00006 instead of 6e-5)
		out << std::fixed << runtime << std::endl;
		std::cout << i << ": " << std::fixed << runtime << std::endl;
		// Increase global counter to calculate different fibonacci value.
		TIMER_N++;
	}
	out.close();
}

size_t fibonacci(int n)
{
	if (n <= 0)
	{
		std::cout << "Warning: Fibonacci not defined for values less than 1.\n";
		return 0;
	}

	if (n > 3500)
	{
		std::cout << "Too large n - Aborting to avoid stackoverflow.\n";
		return 0;
	}

	// Recursion floor: n less than 2. return 1 to achieve characteristic fibonacci function.
	if (n <= 2)
	{
		return 1;
	}
	else {
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}
void fib_timed()
{
	size_t fib(fibonacci(TIMER_N));
	// Something needs to be done with the value <fib>, so we print it.
	// Else, it will be "optimized away" in the release version, because the variable is never used.
	std::cout << fib << ": ";
}