#ifndef HELPER_FUNCS_H
#define HELPER_FUNCS_H
#include<iostream>
#include<vector>
using std::string;
using std::vector;

// Compares two strings. Returns 0 if equal, -1 if smaller and +1 if greater than the other string. (lexicographically)
int strcmp(string const& name1, string const& name2)
{
	if (name1.length() != name2.length())
	{
		return -1;
	}

	string tmp1 = name1;
	string tmp2 = name2;

	for (size_t n(0); n < name1.length(); n++)
	{
		tmp1[n] = std::tolower(name1[n]);
		tmp2[n] = std::tolower(name2[n]);
	}

	return tmp1.compare(tmp2);
}

// Returns a vector of elements separated by the specified delimiter
vector<string> split_string(string const& str, char const delimiter)
{
	int offset(0);
	int element_end(0);
	std::vector<string> elements;

	while (str.find(delimiter, offset) != string::npos)
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


#endif