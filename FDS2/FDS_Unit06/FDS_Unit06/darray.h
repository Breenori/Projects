#ifndef DARRAY_H
#define DARRAY_H
#include<string>

typedef std::string data_type;

class darray {
private:
	data_type** m_table;
	size_t m_rows;
	static const size_t m_cols = 20;
	size_t m_max_size;

public:
	darray(); // ctr
	darray(size_t const size);
	~darray(); // destruktor: called when a variable is deleted

	void clear();
	void initialize(size_t const size);
	size_t get_max_size() const;
	data_type& at(size_t const pos);
	data_type get(size_t const pos) const;
	bool set(data_type const data, size_t const pos);
};

void test() {
	darray dyn(10000); // local variable
	// ...
} // destructor for all local variables is called
#endif