#include "darray.h"
#include<iostream>

//ctr:
darray::darray() : m_table(nullptr)
{
	//m_table = nullptr;
	initialize(100);
}

darray::darray(size_t const size) : m_table(nullptr) 
{
	//m_table = nullptr;
	initialize(size);
}

darray::~darray()
{
	//m_table = nullptr;
	clear();
}

void darray::initialize(size_t const size)
{
	clear();
	this->m_rows = size / m_cols;
	if (size % m_cols != 0)
	{
		++this->m_rows;
	}
	this->m_table = new data_type*[this->m_rows];
	//this->m_table = new element_type[this->m_rows];
	for (size_t i(0); i < this->m_rows; ++i)
	{
		this->m_table[i] = nullptr;
	}

	this->m_max_size = m_rows * m_cols;
}

void darray::clear()
{
	//delete[] all rows, if not null
	// delete[] master table, if not null
	// set m table to nullptr
}

data_type& darray::at(size_t const pos)
{
	size_t row = pos / m_rows;

	if (pos > m_max_size)
	{
		std::cout << "warning: element out of bounds.\n";
		row = pos % m_rows;
	}

	size_t col = pos % m_cols;

	if (m_table[row] == nullptr)
	{
		m_table[row] = new data_type[m_cols];
	}

	return this->m_table[row][col];
}

data_type darray::get(size_t const pos) const 
{
	return at(pos);
}