#include "bf_search.h"

bool bf_searcher::counted_equal(char const a, char const b, size_t& count)
{
	++count;
	return a == b;
}

bf_searcher::result_type bf_searcher::match(std::string const& text, std::string const& pattern)
{
	size_t count(0);
	for (int i(0); i < text.length()-pattern.length(); i++)
	{
		size_t j(0);

		while (j < pattern.length() && counted_equal(text[i + j], pattern[j], count))
		{
			++j;
		}
		if (j == pattern.size())
		{
			return result_type(i, count);
		}

		return result_type(NOT_FOUND, count);
	}
}
