#include "dynamic_array.h"
#include<iostream>
#include<iomanip>

dynamic_array::dynamic_array() : m_table(nullptr)
{
	initialize(100);
}

dynamic_array::dynamic_array(size_t const size) : m_table(nullptr)
{
	initialize(size);
}

dynamic_array::~dynamic_array()
{
	clear();
}

void dynamic_array::initialize(size_t const size)
{
	// First, everything inside the array is being cleared.
	clear();

	if (size > 0)
	{
		// Then, the amount of rows needed to accomodate <size> elements is being calculated and allocated.
		this->m_rows = size / m_cols;
		if (size % m_cols != 0)
		{
			++this->m_rows;
		}
		this->m_table = new data_type * [this->m_rows];

		// Finally, every row is being set to a nullptr until they're needed later. 
		for (size_t i(0); i < this->m_rows; ++i)
		{
			this->m_table[i] = nullptr;
		}

		// Save the amount of maximum allowed elements.
		this->m_max_size = size;
	}
}

size_t dynamic_array::get_max_size() const
{
	return this->m_max_size;
}

void dynamic_array::clear()
{
	// If the table is not a nullpointer (initialized), every row is deleted first 
	if (m_table != nullptr)
	{
		for (size_t row(0); row < m_rows; row++)
		{
			if (m_table[row] != nullptr)
			{
				delete[] m_table[row];
			}
		}

		// Afterwards the table itself is deleted and set to nullptr to avoid access violations.
		delete[] m_table;
		m_table = nullptr;
	}
	
	// Finally all the changeable values are set to zero.
	m_rows = 0;
	m_max_size = 0;
}

data_type& dynamic_array::at(size_t const pos)
{
	// First we calculate the row and col using the given position <pos>
	size_t row;
	size_t col;
	get_coordinates(pos, row, col);

	// If the row is null, we allocate new memory.
	if (m_table[row] == nullptr)
	{
		m_table[row] = new data_type[m_cols];
	}

	return this->m_table[row][col];
}

data_type dynamic_array::get(size_t const pos) const
{
	// First we calculate the row and col using the given position <pos>
	size_t row;
	size_t col;
	get_coordinates(pos, row, col);

	// If the specified row is null, we can't get the specified element at <pos> so we print a warning and return an empty string.
	if (m_table[row] == nullptr)
	{
		std::cout << "ERROR: No value found at position " << pos << ".\n";
		return data_type();
	}

	return this->m_table[row][col];
}

bool dynamic_array::set(data_type const data, size_t const pos)
{
	// If the users wants to set a position out of bounds we return false and do nothing.
	if (pos >= m_max_size)
	{
		std::cout << "ERROR: Index out of bounds! Couldn't set value at position " << pos << std::endl;
		return false;
	}

	// First we calculate the row and col using the given position <pos>
	size_t row;
	size_t col;
	get_coordinates(pos, row, col);

	// If the specified row the element is in is null, we allocate new memory first and then set it.
	if (m_table[row] == nullptr)
	{
		m_table[row] = new data_type[m_cols];
	}

	m_table[row][col] = data;

	return true;
}

bool dynamic_array::get_coordinates(size_t const pos, size_t& row, size_t& col) const
{
	// Create a flag to determine whether the index was out of bounds (and a correction was applied)
	bool okay(true);

	

	// If the index is out of bounds, apply correction and change flag.
	if (pos >= m_max_size)
	{
		std::cout << "WARNING: Position " << pos << " out of bounds. Applying correction.\n";
		okay = false;
	}

	row = (pos % m_max_size) / m_cols;
	col = (pos % m_max_size) % m_cols;

	return okay;
}

void dynamic_array::print(std::ostream& out) const
{
	// If the table is initialized, print every initialized row and every column.
	if (m_table != nullptr)
	{
		for (size_t row(0); row < m_rows; row++)
		{
			out << "Row " << row + 1 << ": ";
			if (m_table[row] != nullptr)
			{
				for (size_t col(0); col < m_cols; col++)
				{
					if (col >= 1)
					{
						out << ";";
					}
					out << "\"" << m_table[row][col] << "\"";
				}
			}
			// For empty rows, print "<empty>" for clarity
			else
			{
				std::cout << "<empty>";
			}
			out << std::endl;
		}
	}
}

bool dynamic_array::empty()
{
	return m_table == nullptr;
}
