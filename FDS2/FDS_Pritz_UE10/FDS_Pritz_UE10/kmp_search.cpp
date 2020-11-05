#include "kmp_search.h"

std::vector<int> kmp_search::compute_prefix_function(std::string const& pattern)
{
	std::vector<int> lp;		// = leap table
	size_t pos_pattern(0);
	int prefix_size(-1);

	// First entry will always be -1 (can't jump back to origin)
	lp.push_back(prefix_size);

	while (pos_pattern < pattern.size())
	{
		// Determine current positions prefix length
		while (prefix_size >= 0 && pattern[pos_pattern] != pattern[prefix_size])
		{
			prefix_size = lp[prefix_size];
		}

		pos_pattern++;
		prefix_size++;
		lp.push_back(prefix_size);
	}

	return lp;
}


int kmp_search::match(std::string const& text, std::string const& pattern, size_t const start_pos)
{
	if (pattern.size() > 0 && text.size() > pattern.size())
	{
		// Calculate leap table
		std::vector<int> lp = kmp_search::compute_prefix_function(pattern);

		size_t pos_text(start_pos);
		int pos_pattern(0);

		while (((pos_text < text.size()) && (pos_pattern < pattern.size()))) {

			while (pos_pattern >= 0 && text[pos_text] != pattern[pos_pattern])
			{
				pos_pattern = lp[pos_pattern];
			}

			pos_text++;
			pos_pattern++;
		}

		return pos_pattern == pattern.size() ? pos_text - pattern.size() : kmp_search::NOT_FOUND;
	}
	return kmp_search::NOT_FOUND;
}
int kmp_search::match(std::string const& text, std::string const& pattern, datacollector& dc, size_t const start_pos)
{
	if (pattern.size() > 0 && text.size() > pattern.size())
	{
		// Calculate leap table
		std::vector<int> lp = kmp_search::compute_prefix_function(pattern);

		size_t pos_text(start_pos);
		int pos_pattern(0);

		while (((pos_text < text.size()) && (pos_pattern < pattern.size()))) {

			while (pos_pattern >= 0 && !dc.counted_equal(text[pos_text], pattern[pos_pattern]))
			{
				pos_pattern = lp[pos_pattern];
			}

			pos_text++;
			pos_pattern++;
		}

		return pos_pattern == pattern.size() ? pos_text - pattern.size() : kmp_search::NOT_FOUND;
	}
	return kmp_search::NOT_FOUND;
}



