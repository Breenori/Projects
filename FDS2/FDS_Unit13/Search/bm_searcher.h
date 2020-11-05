#ifndef BM_SEARCHER_H
#define BM_SEARCHER_H
#include<iostream>
#include<vector>

class bm_searcher
{
public:
	typedef std::pair<int, size_t> result_type;
	typedef std::vector<size_t> shift_function_type;
	static const int NOT_FOUND = -1;

	static result_type match(std::string const& text, std::string const& pattern);
	static shift_function_type compute_shift_function(std::string const& pattern);
	static bool counted_equal(char const a, char const b, size_t& count);
};

#endif