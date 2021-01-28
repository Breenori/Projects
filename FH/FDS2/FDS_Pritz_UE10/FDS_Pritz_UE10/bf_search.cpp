#include "bf_search.h"

int bf_search::match(std::string const& text, std::string const& pattern, datacollector& dc, size_t const start_pos)
{
	if (pattern.size() > 0 && text.size() > pattern.size())
	{
		size_t count(0);
		// Search for the pattern at every position in text.
		for (int text_pos(start_pos); text_pos <= text.length() - pattern.length(); text_pos++)
		{
			size_t pattern_pos(0);

			// Try to find it per position by advancing in the pattern
			while (pattern_pos < pattern.length() && dc.counted_equal(text[text_pos + pattern_pos], pattern[pattern_pos]))
			{
				pattern_pos++;
			}
			if (pattern_pos == pattern.size())
			{
				return text_pos;
			}
		}
	}
	return NOT_FOUND;
}
int bf_search::match(std::string const& text, std::string const& pattern, size_t const start_pos)
{
	if (pattern.size() > 0 && text.size() > pattern.size())
	{
		size_t count(0);
		// Search for the pattern at every position in text.
		for (int text_pos(start_pos); text_pos <= text.length() - pattern.length(); text_pos++)
		{
			size_t pattern_pos(0);

			// Try to find it per position by advancing in the pattern
			while (pattern_pos < pattern.length() && text[text_pos + pattern_pos] == pattern[pattern_pos])
			{
				++pattern_pos;
			}
			if (pattern_pos == pattern.size())
			{
				return text_pos;
			}
		}
	}
	return NOT_FOUND;
}
