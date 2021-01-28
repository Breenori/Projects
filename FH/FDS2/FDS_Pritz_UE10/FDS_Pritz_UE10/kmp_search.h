#ifndef KMP_SEARCH_H
#define KMP_SEARCH_H
#include<iostream>
#include<vector>
#include "datacollector.h"

class kmp_search
{
public:
	// Returns the position where the pattern has been found.
	// Returns bf_search::NOT_FOUND if it hasn't been found.
	static int match(std::string const& text, std::string const& pattern, size_t const start_pos = 0);
	// Returns the position where the pattern has been found.
	// Returns bf_search::NOT_FOUND if it hasn't been found.
	// This version collects more information to better understand the algorithms.
	static int match(std::string const& text, std::string const& pattern, datacollector& dc, size_t const start_pos = 0);
	// The value returned when pattern couldnt be found.
	static const int NOT_FOUND = -1;

	// Returns a prefix based shift table for kmp based on the pattern.
	static std::vector<int> compute_prefix_function(std::string const& pattern);
};

#endif