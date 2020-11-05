#ifndef BF_SEARCH_H
#define BF_SEARCH_H
#include<string>

class bf_searcher
{
public:
	typedef std::pair<int, size_t> result_type;
	static result_type match(std::string const& text, std::string const& pattern);
	static const int NOT_FOUND = -1;
private:
	static bool counted_equal(char const a, char const b, size_t& count);
};

#endif