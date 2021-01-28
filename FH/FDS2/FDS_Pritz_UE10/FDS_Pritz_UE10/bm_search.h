#ifndef BM_SEARCH_H
#define BM_SEARCH_H
#include "datacollector.h"

class bm_search
{
public:
	typedef std::vector<size_t> shift_function_type;

	// Returns the position where the pattern has been found.
	// Returns bf_search::NOT_FOUND if it hasn't been found.
	static int match(std::string const& text, std::string const& pattern, size_t const start_pos = 0);
	// Returns the position where the pattern has been found.
	// Returns bf_search::NOT_FOUND if it hasn't been found.
	// This version collects more information to better understand the algorithms.
	static int match(std::string const& text, std::string const& pattern, datacollector& dc, size_t const start_pos = 0);
	// The value returned when pattern couldnt be found.
	static const int NOT_FOUND = -1;

	// Returns a shift table for boyer moore search based on the pattern.
	static shift_function_type compute_shift_function(std::string const& pattern);
};

#endif