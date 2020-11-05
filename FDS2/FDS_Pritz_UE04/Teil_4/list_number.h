#ifndef LIST_NUMBER_H
#define LIST_NUMBER_H
#include<string>
#include "slist.h"

class list_number_t {
public:
	// Sign type for numbers
	enum class sign_t { SIGN_NEGATIVE, SIGN_POSITIVE };
	// Default constructor. Empty list.
	list_number_t();
	//  delegates to default constructor and initialize
	list_number_t(std::string const& s);
	// Default deconstructor
	~list_number_t();
	// Initializes the list using a string.
	void initialize(std::string const& s);
	// Sets the sign of the number
	void set_sign(sign_t const sign);
	// Compares the number to another list_number_t
	// Returns 0 if equal, 1 if greater than cmp, and -1 if less than cmp.
	int compare(list_number_t const& cmp) const;
	// Prints the number.
	void print() const;
	// Clears the list.
	void clear();
private: 
	// Stores the state of the number
	slist list;
	sign_t sign;
	int compare_wrapper(list_number_t const& cmp, size_t const index) const;
};

#endif