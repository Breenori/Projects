#include "pfc-mini.hpp"

const uint32_t N = 1000 * 1000 * 1000; // Number of iterations
const size_t m = 6; // Number of variables

void for_loop()
{
	double a(10), b(391), c(2103), d(111), e(123), z(0);

	for (uint32_t i(0); i < N; i++)
	{
		z = a;
		z = b;
		z = c;
		z = d;
		z = e;
	}
}
void for_loop_division()
{
	double a(10), b(391), c(2103), d(111), e(123), z(0);

	for (uint32_t i(0); i < N; i++)
	{
		z = a / b;
		z = b / a;
		z = c / b;
		z = d / c;
		z = e / d;
	}
	
}

void main()
{
	double for_loop_time(pfc::in_s(pfc::timed_run(for_loop)));
	std::cout << for_loop_time << " [sec]\n";
	double for_loop_division_time(pfc::in_s(pfc::timed_run(for_loop_division)));
	std::cout << for_loop_division_time << " [sec]\n";
	double time_division((for_loop_division_time - for_loop_time) / N / m);
	std::cout << time_division * 1000 * 1000 * 1000 << " [nsec]\n";
}