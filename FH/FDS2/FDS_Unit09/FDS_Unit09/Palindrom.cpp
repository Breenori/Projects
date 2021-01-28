#include<iostream>
#include<string>


bool is_palindrom(std::string str);
bool is_palindrom_wrapper(std::string str, size_t start, size_t end);

/*void main()
{
	if (is_palindrom("GNUDUNG"))
	{
		std::cout << "This is a palindrome.";
	}
}*/

bool is_palindrom(std::string str)
{
	return is_palindrom_wrapper(str, 0, str.size() - 1);
}
bool is_palindrom_wrapper(std::string str, size_t start, size_t end)
{
	if (start >= end)
	{
		return true;
	}
	else if (std::toupper(str[start]) == std::toupper(str[end]))
	{
		return is_palindrom_wrapper(str, start + 1, end - 1);
	}
	else
	{
		return false;
	}
}