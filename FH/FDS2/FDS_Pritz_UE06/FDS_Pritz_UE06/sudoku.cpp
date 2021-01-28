#include "sudoku.h"
#include<fstream>
#include<regex>
#include<iomanip>
#include "string_functions.h"

sudoku_t::sudoku_t()
{
	initialized = false;
	p_sudoku = nullptr;
	p_simplified_sudoku = nullptr;
	n = 0;
	rowsize = 0;
}
sudoku_t::~sudoku_t()
{
	clear();
}

bool sudoku_t::initialize(std::string const& f_name)
{
	std::ifstream in(f_name);
	bool tmp(read(in));
	in.close();
	return tmp;
}
bool sudoku_t::read(std::istream& in)
{
	// Only read in if inputstream is good.
	if (in)
	{
		std::string line;
		std::regex num("^[0-9]+$");
		if (std::getline(in, line) && std::regex_match(line, num))
		{
			// Convert line to int and calculate important figures.
			n = std::stoi(line);
			rowsize = n * n;

			// if n is valid.
			if (n > 1)
			{
				p_sudoku = new size_t * [rowsize];
				for (size_t i(0); i < rowsize; i++)
				{
					p_sudoku[i] = new size_t[rowsize];
				}

				bool okay(true);
				size_t cur_index(0);

				std::vector<std::string> tmp;

				// Get values from each line.
				while (getline(in, line) && okay && cur_index < std::pow(n, 4))
				{
					tmp = split_string(line, '|');

					// make sure the line has sufficient numbers
					if (tmp.size() - 1 != rowsize)
					{
						okay = false;
					}
					else
					{

						// Convert each number into an int if numeric and save it into the carray
						for (int i(1); i < tmp.size(); i++)
						{
							if (std::regex_match(tmp[i], num))
							{
								int value(std::stoi(tmp[i]));
								if (value >= 0 || value <= rowsize)
								{
									p_sudoku[cur_index / rowsize][cur_index % rowsize] = value;
									cur_index++;
								}
								else
								{
									if (okay)
									{
										std::cout << "Error: Value out of bounds!\n";
									}
									okay = false;
								}
							}
							else
							{
								if (okay)
								{
									std::cout << "Error: Non-numeric value found!\n";
								}
								okay = false;
							}
						}
					}
				}

				// if the amount of read in numbers differs from the amount of fields we quit.
				if (!okay)
				{
					std::cout << "Error: Corrupt file.\n";
				}
				else
				{
					initialized = true;
					return true;
				}
			}
			else
			{
				std::cout << "Number of blocks must be greater than 1!\n";
			}
		}
	}
	return false;
}

void sudoku_t::simplify()
{
	if (initialized)
	{
		// Create a carray of slists of sufficient length for the possibilities
		p_simplified_sudoku = new slist * [rowsize];
		for (size_t i(0); i < rowsize; i++)
		{
			p_simplified_sudoku[i] = new slist[rowsize];
		}

		// For each field, get all possibilities
		for (size_t row(0); row < rowsize; row++)
		{
			for (size_t col(0); col < rowsize; col++)
			{
				if (p_sudoku[row][col] == 0)
				{
					// Fill a list with all possible values. Then remove them.
					p_simplified_sudoku[row][col].init(rowsize);

					get_simplified_values(p_simplified_sudoku[row][col], row, col);
				}
			}
		}

		// Then, if ONLY ONE possibility exists for a field, put it in and update the possibilites of affected fields.
		// repeat the process until the simplified carray remains unchanged

		bool simplified(true);
		while (simplified)
		{
			simplified = false;
			for (size_t row(0); row < rowsize; row++)
			{
				for (size_t col(0); col < rowsize; col++)
				{
					if (p_simplified_sudoku[row][col].size() == 1)
					{
						p_sudoku[row][col] = p_simplified_sudoku[row][col].get(0);
						p_simplified_sudoku[row][col].clear();

						remove_possibilities(row, col);
						simplified = true;
					}
				}
			}
		}
	}
	else
	{
		std::cout << "Error: Unable to simplify. Please initialize first.\n";
	}
}
void sudoku_t::get_simplified_values(slist& list, size_t const i_row, size_t const i_col)
{
	// Go through every field in the same column and remove populated fields from the possibilities.
	for (size_t row(0); row < rowsize; row++)
	{
		if (p_sudoku[row][i_col] != 0)
		{
			list.remove_all(p_sudoku[row][i_col]);
		}
	}

	// Go through every field in the same row and remove populated fields from the possibilities.
	for (size_t col(0); col < rowsize; col++)
	{
		if (p_sudoku[i_row][col] != 0)
		{
			list.remove_all(p_sudoku[i_row][col]);
		}
	}

	// calculate which block the index is located in.
	size_t field_row((i_row / n) * n);
	size_t field_col((i_col / n) * n);

	// Go through every field in the same block and remove populated fields from the possibilities.
	for (size_t row(field_row); row < field_row + n; row++)
	{
		for (size_t col(field_col); col < field_col + n; col++)
		{
			if (p_sudoku[row][col] != 0)
			{
				list.remove_all(p_sudoku[row][col]);
			}
		}
	}
}

void sudoku_t::solve()
{
	// The sudoku must have been read in before we can solve it.
	if (initialized)
	{
		solve_helper(0);
	}
	else
	{
		std::cout << "Error: Unable to solve sudoku. Please initialize first.\n";
	}
}
bool sudoku_t::solve_helper(size_t const index)
{
	size_t row(index / rowsize);
	size_t col(index % rowsize);
	// If we are at the end of the list, we need to check it and possibly return true.
	if (index == rowsize * rowsize)
	{
		return true;
	}
	// If the value at the index is 0 we have to evaluate.
	else if (p_sudoku[row][col] == 0)
	{
		size_t counter(0);
		bool done(false);

		slist updated_indices;

		// Try out all possibilities
		while (counter < p_simplified_sudoku[row][col].size() && !done)
		{
			// Try out the value and remove the possibility for all other affected fields.
			p_sudoku[row][col] = p_simplified_sudoku[row][col].get(counter);

			// Save all the indices that have had their possibilities reduced to restore them later.
			updated_indices.clear();
			updated_indices.copy_from(remove_possibilities(row, col));

			// Try to solve the next field with the current field populated.
			done = solve_helper(index + 1);

			// If solving it didnt work with this possibility, reset it to 0 and restore possibilities for all affected fields.
			// Then try the next possibility for this field!
			if (!done)
			{
				restore_possibilities(p_sudoku[row][col], updated_indices);
				p_sudoku[row][col] = 0;
				counter++;
			}
		}
		return done;
	}
	else
	{
		// If the value isn't zero, skip this field.
		return solve_helper(index + 1);
	}
}

slist sudoku_t::remove_possibilities(size_t const i_row, size_t const i_col)
{
	slist updated;

	// Update the possibilites for the whole column.
	for (size_t row(0); row < rowsize; row++)
	{
		if (p_simplified_sudoku[row][i_col].contains(p_sudoku[i_row][i_col]))
		{
			p_simplified_sudoku[row][i_col].remove_all(p_sudoku[i_row][i_col]);

			// Save the index of the updated field to restore the possibility later.
			updated.push_back(row * rowsize + i_col);
		}
	}

	// Update the possibilites for the whole row.
	for (size_t col(0); col < rowsize; col++)
	{
		if (p_simplified_sudoku[i_row][col].contains(p_sudoku[i_row][i_col]))
		{
			p_simplified_sudoku[i_row][col].remove_all(p_sudoku[i_row][i_col]);
			if (!updated.contains(i_row * rowsize + col))
			{
				updated.push_back(i_row * rowsize + col);
			}
		}
	}

	// Update the possibilites for the whole sub-block.
	size_t field_row((i_row / n) * n);
	size_t field_col((i_col / n) * n);

	for (size_t row(field_row); row < field_row + n; row++)
	{
		if (row != i_row)
		{
			for (size_t col(field_col); col < field_col + n; col++)
			{
				if (col != i_col)
				{
					if (p_simplified_sudoku != nullptr)
					{
						if (p_simplified_sudoku[row][col].contains(p_sudoku[i_row][i_col]))
						{
							p_simplified_sudoku[row][col].remove_all(p_sudoku[i_row][i_col]);
							if (!updated.contains(row * rowsize + col))
							{
								updated.push_back(row * rowsize + col);
							}
						}
					}
				}
			}
		}
	}

	return updated;
}
void sudoku_t::restore_possibilities(size_t const item, slist const& restore_list)
{
	// Iterate through the indices and restore the previous possibility set
	for (size_t i(0); i < restore_list.size(); i++)
	{
		slist::value_t tmp(restore_list.get(i));
		p_simplified_sudoku[tmp / rowsize][tmp % rowsize].insert_sorted(item);
	}
}

bool sudoku_t::check() const
{
	if (initialized)
	{
		// Check all rows for double values.
		slist s;
		for (size_t row(0); row < rowsize; row++)
		{
			s.init(rowsize);

			for (size_t col(0); col < rowsize; col++)
			{
				s.remove_all(p_sudoku[row][col]);
			}

			// If there's values remaining, theres a double.
			if (!s.empty())
			{
				return false;
			}
		}

		// Check all columns for double values.
		for (size_t col(0); col < rowsize; col++)
		{
			s.init(rowsize);

			for (size_t row(0); row < rowsize; row++)
			{
				s.remove_all(p_sudoku[row][col]);
			}

			// If there's values remaining, theres a double.
			if (!s.empty())
			{
				return false;
			}
		}

		// Check all sub_blocks for double values.
		for (size_t sector_y(0); sector_y < n; sector_y++)
		{
			for (size_t sector_x(0); sector_x < n; sector_x++)
			{
				// Fill a list with all possible values. Then remove them.
				s.init(rowsize);

				for (size_t row(sector_y* n); row < sector_y * n + n; row++)
				{
					for (size_t col(sector_x* n); col < sector_x * n + n; col++)
					{
						s.remove_all(p_sudoku[row][col]);
					}
				}

				if (!s.empty())
				{
					return false;
				}
			}
		}

		return true;
	}
	else
	{
		std::cout << "Error: Unable to check sudoku. Please initialize first.\n";
		return false;
	}
}

void sudoku_t::print(std::ostream& out) const
{
	if (initialized)
	{
		out << std::endl;

		// Get the "width" or amount of figures per n
		// ex for n=5: 25 = 2 figures. 2 and 5.
		size_t numwidth(get_max_figures() + 1);
		// Width = amount of numbers per row * figures ( +1 for spaces) + n spaces at the end + (n+1) vertical separators.
		size_t width(rowsize * (numwidth + 1) + n + (n + 1));

		// Print the upper line
		for (size_t count(0); count < width; count++)
		{
			out << '-';
		}
		out << std::endl;
		for (size_t row(0); row < rowsize; row++)
		{
			// If a all blocks of a row are completed, print a line.
			if (row % n == 0 && row != 0)
			{

				for (size_t count(0); count < width; count++)
				{
					out << '-';
				}
				out << std::endl;
			}
			// Print at start of each line
			out << '|' << " ";
			for (size_t col(0); col < rowsize; col++)
			{
				size_t index(row * rowsize + col);
				// Print inner vertical dividers.
				if (col % n == 0 && (index % rowsize) != 0)
				{
					out << '|' << " ";
				}

				// If populated, print the value.
				if (p_sudoku[row][col] != 0)
				{
					out << std::setw(numwidth) << p_sudoku[row][col];
				}
				else
				{
					out << std::setw(numwidth) << " ";
				}

				out << " ";
			}
			// Print at end of line
			out << '|' << std::endl;
		}
		// Print bottom line
		for (size_t count(0); count < width; count++)
		{
			out << '-';
		}

		out << std::endl;
	}
	else
	{
		std::cout << "Error: Unable to print Sudoku. Please initialize first.\n";
	}
}
size_t sudoku_t::get_max_figures() const
{
	if (initialized)
	{
		std::string tmp(std::to_string(rowsize));
		return tmp.length();
	}
	else
	{
		return 0;
	}
}

void sudoku_t::clear()
{
	if (p_sudoku != nullptr)
	{
		for (size_t n(0); n < rowsize; n++)
		{
			if (p_sudoku[n] != nullptr)
			{
				delete[] p_sudoku[n];
			}
		}
		delete[] p_sudoku;
		p_sudoku = nullptr;
	}
	if (p_simplified_sudoku != nullptr)
	{
		delete[] p_simplified_sudoku;
		p_simplified_sudoku = nullptr;
	}

	initialized = false;
	n = 0;
	rowsize = 0;
}