#include "bm_search.h"

int bm_search::match(std::string const& text, std::string const& pattern, datacollector& dc, size_t const start_pos)
{
	if (pattern.size() > 0 && text.size() > pattern.size())
	{
		// Compute shift table based on the pattern
		shift_function_type shift_table(compute_shift_function(pattern));
		size_t pos_text(start_pos);

		// Start pattern searching from behind
		int pos_pattern(pattern.size() - 1);

		do
		{
			// Advance reversed in the pattern as long as pattern equals text at the position
			while (pos_pattern >= 0 && dc.counted_equal(text[pos_text + pos_pattern], pattern[pos_pattern]))
			{
				pos_pattern--;
			}

			// begin of pattern passed = if pattern fully found
			if (pos_pattern < 0)
			{
				return pos_text;
			}

			// If it hasn't been found, go forward based on the shift_table and reverse pattern progress
			pos_text += shift_table[(unsigned char)text[pos_text + pattern.size() - 1]];
			pos_pattern = pattern.size() - 1;

		} while (pos_text <= text.size() - pattern.size());
	}
	return NOT_FOUND;
}

int bm_search::match(std::string const& text, std::string const& pattern, size_t const start_pos)
{
	if (pattern.size() > 0 && text.size() > pattern.size())
	{
		// Compute shift table based on the pattern
		shift_function_type shift_table(compute_shift_function(pattern));
		size_t pos_text(start_pos);

		// Start pattern searching from behind
		int pos_pattern(pattern.size() - 1);

		// Advance reversed in the pattern as long as pattern equals text at the position
		do
		{
			while (pos_pattern >= 0 && text[pos_text + pos_pattern] == pattern[pos_pattern])
			{
				pos_pattern--;
			}

			// begin of pattern passed = if pattern fully found
			if (pos_pattern < 0)
			{
				return pos_text;
			}

			// If it hasn't been found, go forward based on the shift_table and reverse pattern progress
			pos_text += shift_table[text[pos_text + pattern.size() - 1]];
			pos_pattern = pattern.size() - 1;

		} while (pos_text <= text.size() - pattern.size());
	}
	return NOT_FOUND;
}

bm_search::shift_function_type bm_search::compute_shift_function(std::string const& pattern)
{
	shift_function_type shift_table(256, pattern.length());

	// For each character, check how far it is from the end of the pattern to calculate the maximum shift.
	for (size_t i(0); i < pattern.size() - 1; ++i)
	{
		shift_table[pattern[i]] = pattern.size() - i - 1;
	}

	return shift_table;
}

