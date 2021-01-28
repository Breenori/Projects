#ifndef SUDOKU_H
#define SUDOKU_H
#include<iostream>
#include "slist.h"

class sudoku_t {
public:
	//Constructor
	sudoku_t();
	//Deconstructor
	~sudoku_t();
	// Initialize the sudoku by reading in from a file.
	// Returns whether the read-in process was successful.
	bool initialize(std::string const& f_name);
	// Reads in a sudoku configuration from specified stream
	bool read(std::istream& in);
	// Simplfies the sudoku by ruling out impossible combinations.
	void simplify();
	// Tries to solve the sudoku recursively.
	void solve();
	// Returns whether the sudoku was solved correctly.
	bool check() const;
	// Prints the sudoku to the designated outputstream.
	void print(std::ostream& out = std::cout) const;
	// Delete all allocated memory and reset values to default.
	void clear();
private:
	// The carray of numbers containing the sudoku fields.
	size_t** p_sudoku;
	// The carray containing all possibilities for each field.
	slist** p_simplified_sudoku;
	// The width/height of each subblock and amount of subblocks next to each other.
	size_t n;
	// The amount of fields per row/column.
	size_t rowsize;
	// Saves whether the class has been initialized.
	bool initialized;
	// Simplifies the possibilities by removing all impossible values from the given list.
	void get_simplified_values(slist& list, size_t const i_row, size_t const i_col);
	// Recursive wrapper for the solve() function.
	bool solve_helper(size_t const index);
	// Removes all possibilities based on the new value put on the index.
	// Saves all the altered fields to <updated>
	slist remove_possibilities(size_t const row, size_t const col);
	// Restores the state of fields to before "remove_possibilities" did it's job.
	// <restore_list> contains all indices that need to be restored.
	void restore_possibilities(size_t const item, slist const& restore_list);
	// Calculates the maximum number of digits for output width.
	size_t get_max_figures() const;
};
#endif