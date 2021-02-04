#include <iostream>
#include "syntax_tree.h"
#include "parser.h"
#include "divide_by_zero_exception.h"
#include<fstream>

using namespace xpr;

void test_functionality()
{
	std::istringstream in("set (a,0.25+0.25); set (b, 9+(9^a*12)/6-5); print (b);"); // returns 10

	ParseSyntaxTree pst(in);

	try {
		pst.parse();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
}
void test_divbyzero()
{
	std::istringstream in("set (a,0); set (b, 10/a); print (b);"); // divide by zero exception

	ParseSyntaxTree pst(in);

	try {
		pst.parse();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
}
void test_parseexcept()
{
	std::istringstream in("set (a,0+);"); // parse exception

	ParseSyntaxTree pst(in);

	try {
		pst.parse();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
}
void test_varnotfound()
{
	std::istringstream in("print (pepehands);"); // variable not found exception

	ParseSyntaxTree pst(in);

	try {
		pst.parse();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
}
void test_invalidvar()
{
	std::istringstream in("set (1, b);");

	ParseSyntaxTree pst(in);

	try {
		pst.parse();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
}
void test_printall()
{
	std::istringstream in("set (a, 2^2*4); set (b, a^0.5); set (x, a+b);"); // variable not found exception

	ParseSyntaxTree pst(in);

	try {
		pst.parse();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::ofstream out("printed_trees.txt");

	pst.print_all_variables(out);

	out.close();
}
void test_cycle()
{
	// crashes. could be prevented by adding each evaluated variable (per expression) to a list and checking if it has already been evaluated.
	std::istringstream in("set (a, b); set(b, a); print(b);"); // cycle

	ParseSyntaxTree pst(in);

	try {
		pst.parse();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void main()
{
	test_functionality();
	//test_divbyzero();
	//test_parseexcept();
	//test_varnotfound();
	//test_invalidvar();
	//test_printall();
	//test_cycle();
}