#include "sudoku.h"
#include "pfc-mini.hpp"
#include<iostream>
#include<fstream>


const std::string filename("input/test3.txt");

void solve_sudoku();

void main()
{
	// Print out the time needed for initializing, simplifying, solving, checking and printing the sudoku.
	std::cout << pfc::in_s(pfc::timed_run(solve_sudoku)) << " [seconds]\n";
}

void solve_sudoku()
{
	sudoku_t sudoku;
	sudoku.initialize(filename);
	sudoku.print();
	sudoku.simplify();
	sudoku.print();
	sudoku.solve();
	sudoku.print();

	if (sudoku.check())
	{
		std::cout << "Sudoku was solved properly!";
	}
	else
	{
		std::cout << "Sudoku was solved incorrectly!";
	}

	std::cout << std::endl;
}

