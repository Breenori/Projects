#include "list_number.h"
#include<regex>

list_number_t::list_number_t()
{
	this->list = slist();
	this->sign = sign_t::SIGN_POSITIVE;
}

list_number_t::list_number_t(std::string const& s) : list_number_t()
{
	initialize(s);
}

list_number_t::~list_number_t()
{
	this->list.clear();
}

void list_number_t::initialize(std::string const& s)
{
	this->clear();
	// Check if the given string only contains numbers.
	std::regex onlynumber("^[0-9]+$");
	if (std::regex_match(s, onlynumber))
	{
		// If it's only numbers, divide them into chunks of 3 from the back and add them as nodes.
		for (int n(s.size()); n > 0; n -= 3)
		{
			if (n - 3 > 0)
			{
				this->list.push_front(std::stoi(s.substr(n-3, 3)));
			}
			else
			{
				this->list.push_front(std::stoi(s.substr(0, n)));
			}
		}
	}
	// If the string doesn't contain numbers only print an error.
	else
	{
		std::cout << "The string contains invalid characters. Aborting..." << std::endl;
		std::cout << "String: " << s << std::endl;
		std::cout << "NOTE: Don't include sign in initialization. Use corresponding function." << std::endl;
	}
}

void list_number_t::set_sign(sign_t const sign)
{
	this->sign = sign;
}

int list_number_t::compare(list_number_t const& cmp) const
{
	// If the sign differs, instantly return which is greater.
	if (this->sign != cmp.sign)
	{
		return this->sign == sign_t::SIGN_POSITIVE ? 1 : -1;
	}

	// If the size differs, return result.
	if (this->list.size() != cmp.list.size())
	{
		return this->list.size() > cmp.list.size() ? 1 : -1;
	}

	// Else, delegate to wrapper.
	return compare_wrapper(cmp, 0);
}
int list_number_t::compare_wrapper(list_number_t const& cmp, size_t const index) const
{
	// If the index is past the list size, both are equal.
	if (index == this->list.size())
	{
		return 0;
	}

	// Else, values need to be compared.
	slist::value_t v1;
	slist::value_t v2;
	this->list.at(index, v1);
	cmp.list.at(index, v2);
	// If one is lesser/greater than the other, return it.
	if (v1 > v2)
	{
		return 1;
	}
	else if (v1 < v2)
	{
		return -1;
	}
	// Else, repeat the process.
	else
	{
		return compare_wrapper(cmp, index + 1);
	}
}

void list_number_t::print() const
{
	// print the sign
	if (sign == sign_t::SIGN_NEGATIVE)
	{
		std::cout << "-";
	}

	// Print every value, separated with dots.
	slist::value_t value;
	for (size_t i(0); i < this->list.size(); i++)
	{
		if (this->list.at(i, value))
		{
			if (i > 0)
			{
				std::cout << ".";
				// If the value is smaller than 100 or 10, print additional zeroes for chunks of 3.
				if (value / 10 >= 1 && value / 100 < 1)
				{
					std::cout << "0";
				}
				else if (value / 10 < 1)
				{
					std::cout << "00";
				}
			}
			std::cout << value;
		}

	}
	std::cout << std::endl;
}

void list_number_t::clear()
{
	this->list.clear();
}

