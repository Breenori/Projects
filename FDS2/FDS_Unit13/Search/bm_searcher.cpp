#include "bm_searcher.h"

bm_searcher::result_type bm_searcher::match(std::string const& text, std::string const& pattern)
{
	result_type result;
	size_t count_comparison(0);
	shift_function_type shift_table(compute_shift_function(pattern));
	size_t pos_text(0);
	int pos_pattern(pattern.size() - 1);

	do 
	{
		while (pos_pattern >= 0 && counted_equal(text[pos_text + pos_pattern], pattern[pos_pattern], count_comparison))
		{
			pos_pattern--;
		}

		//if pattern fully found
		if (pos_pattern < 0)
		{
			result.first = pos_text;
			result.second = count_comparison;
		}

		pos_text += shift_table[text[pos_text + pattern.size() - 1]];

	} while (pos_text <= text.size() - pattern.size());

	result.first = NOT_FOUND;
	result.second = count_comparison;

	return result;
}

bm_searcher::shift_function_type bm_searcher::compute_shift_function(std::string const& pattern)
{
	shift_function_type shift_table(256, pattern.length());

	for (size_t i(0); i < pattern.size() - 1; ++i)
	{
		shift_table[pattern[i]] = pattern.size() - i - 1;
	}

	return shift_table;
}

bool bm_searcher::counted_equal(char const a, char const b, size_t& count)
{
	++count;
	return a == b;
}
