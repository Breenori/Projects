#include "rational_type.h"
#include "divide_by_zero_exception.h"
#include<iostream>
#include<fstream>
#include "matrix.h"

void test_inverse()
{
	std::cout << "Testcase 1.1: Inverse Test:\n";
	std::cout << "Tests if inverse() function is working.\n";
	rational_t<int> int_rat(5, 1);
	rational_t<double> dbl_rat(1.2, 2.4);
	// Matrix is being skipped due to it not working

	int_rat.inverse();
	dbl_rat.inverse();
	std::cout << "\nExpected: Int = <1/5>, Double = <2/1>\n";
	std::cout << "Actual: ";
	std::cout <<	"Int = " << int_rat << ", " <<
					"Double = " << dbl_rat << std::endl;
	std::cout << std::endl;
}

void test_int_ops()
{
	std::cout << "Testcase 2.1: Calculating with rational_t<int>:\n";
	std::cout << "Testing if calculations still work after applying the template.\n\n";
	rational_t<int> r(-1, 2);

	std::cout	<< r * -10 << std::endl
				<< r * rational_t<int>(20, -2)	<< std::endl;

	r = 7;

	std::cout	<< r + rational_t<int>(2, 3)				<< std::endl
				<< 10 / r / 2 + rational_t<int>(6, 5)	<< std::endl;

	std::cout << std::endl;
}
void test_double_ops()
{
	std::cout << "Testfall 2.2: Calculating with rational_t<double>:\n";
	std::cout << "Testing if calculations still work after applying the template.\n\n";
	rational_t<double> r(-1, 2);

	std::cout << r * -10.0f << std::endl
		<< r * rational_t<double>(20, -2) << std::endl;

	r = -3.1f;

	std::cout << r + rational_t<double>(2, 3) << std::endl
		<< 10 / r / 2 + rational_t<double>(6, 5) << std::endl;

	std::cout << std::endl;
}
void test_matrix_ops()
{
	std::cout << "Testcase 2.3: Calculating with rational_t<Matrix<int>>:\n";
	std::cout << "Testing if calculations still work after applying the template.\n\n";
	/*rational_t<Matrix<int>> r(2, 2);*/
	std::cout << "Doesn't work. More on that matter in the document.\n";
	// Arithmetic operators would function analogous to the ones above, but since the matrix doesn't work im sparing the writing work.
	std::cout << std::endl;
}

void test_matrix()
{
	std::cout << "Testcase 4.1: Testing if creating a rational with matrices works.\n";
	std::cout << "Expected: <2,2>\n";
	// rational_t<Matrix<int>> r(2, 2);
	std::cout << "As already mentioned above I had issues creating the class.\n";
	std::cout << std::endl;
}


void main()
{
	test_inverse();
	
	test_int_ops();
	test_double_ops();
	test_matrix_ops();

	test_matrix();
}


