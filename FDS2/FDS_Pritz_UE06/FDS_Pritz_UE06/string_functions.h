#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H
#include<vector>
#include<string>

// returns an array of elements of a string that are separated by the delmiter
std::vector<std::string> split_string(std::string const& str, char const delimiter);

#endif
