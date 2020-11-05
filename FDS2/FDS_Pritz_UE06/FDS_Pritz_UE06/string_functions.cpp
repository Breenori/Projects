#include "string_functions.h"

std::vector<std::string> split_string(std::string const& str, char const delimiter)
{
	int offset(0);
	int element_end(0);
	std::vector<std::string> elements;

	while (str.find(delimiter, offset) != std::string::npos)
	{
		//calculate where the next delimiter is and get the substring
		int element_end = str.find(delimiter, offset);
		elements.push_back(str.substr(offset, element_end - offset));
		offset = element_end + 1;
	}

	//if there is no more delimiter, but there are still characters after the last delimiter, add the remaining string to the vector
	if (str.length() - 1 >= offset)
	{
		elements.push_back(str.substr(offset, str.length() - offset));
	}

	return elements;
}
