#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include<string>
#include<iostream>

typedef std::string data_type;

class dynamic_array {
private:
	data_type** m_table;
	size_t m_rows;
	static const size_t m_cols = 20;
	size_t m_max_size;

public:
	// Creates a dynamic_array of size 100.
	dynamic_array();
	// Creates a dynamic_array of size <size>.
	dynamic_array(size_t const size);
	// Destructor. Delegates to the clear method upon call.
	~dynamic_array();

	// Frees all dynamically allocated memory (m_table) and resets values to zero (m_rows, m_max_size)
	void clear();
	// Creates an empty matrix with guaranteed access to <size> elements.
	void initialize(size_t const size);
	// Returns the amount of values that have been allocated.
	// Note: Dynamic arrays are always sized multiples of 20.
	size_t get_max_size() const;
	// Returns a reference to an element at position <pos>
	// Note: Entering a position greater than the size will return a new derived position using modulo.
	data_type& at(size_t const pos);
	// Returns the element at position <pos>
	data_type get(size_t const pos) const;
	// Sets the value of an element at position <pos>
	// Returns true if index was in bounds and false if index was out of bound.
	bool set(data_type const data, size_t const pos);
	// Calculates the row and column based on the given position.
	// Returns true if index was in bounds and false if index was out of bound.
	bool get_coordinates(size_t const pos, size_t& row, size_t& col) const;
	// Prints all elements of the dynamic_array to the specified stream <out>
	void print(std::ostream& out = std::cout) const;
	// Returns whether a dynamic_array is empty or not
	bool empty();
};

#endif
