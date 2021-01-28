#include "datacollector.h"
#include<iostream>
datacollector::datacollector()
{
	comparisons = 0;
}
datacollector::datacollector(std::vector<char> const& alphabet)
{
	init(alphabet);
}
datacollector::~datacollector()
{
	reset_statistics();
}

void datacollector::init(std::vector<char> const& alphabet)
{
	// If alphabet size is feasible, initialize the class members.
	if (alphabet.size() <= 256)
	{
		reset_statistics();
		this->alphabet = alphabet;
		success_per_char = std::vector<size_t>(alphabet.size());
		failure_per_char = std::vector<size_t>(alphabet.size());
	}
	else
	{
		std::cout << "Maximum alphabet size is 256. Please try again.\n";
	}
}
void datacollector::reset_statistics()
{
	// Set values to default
	comparisons = 0;
	alphabet.clear();
	success_per_char.clear();
	failure_per_char.clear();
}
void datacollector::log_success(char const character)
{
	// Search for the right characters index in the alphabet and increase its successes if it has been found.
	size_t counter(0);
	while (counter < alphabet.size() && alphabet[counter] != character)
	{
		counter++;
	}

	if (counter < get_alphabet_size())
	{
		success_per_char[counter]++;
	}
}
void datacollector::log_failure(char const character)
{
	// Search for the right characters index in the alphabet and increase its failed comparisons if it has been found.
	size_t counter(0);
	while (counter < alphabet.size() && alphabet[counter] != character)
	{
		counter++;
	}

	if (counter < get_alphabet_size())
	{
		failure_per_char[counter]++;
	}
}
size_t datacollector::get_alphabet_size()
{
	return alphabet.size();
}

size_t datacollector::get_comparison_count()
{
	return comparisons;
}

std::vector<size_t> datacollector::get_success_statistics()
{
	return success_per_char;
}
std::vector<size_t> datacollector::get_failure_statistics()
{
	return failure_per_char;
}
void datacollector::print_statistics(std::ostream& out)
{
	// Prints a csv file with datacollector data
		out << "character;success;failure;total\n";
		for (size_t i(0); i < get_alphabet_size(); i++)
		{
			// Dont print zero value rows
			if (success_per_char[i] > 0 || failure_per_char[i] > 0)
			{
				// Swap control chars in ASCII charset
				if (get_alphabet_size() == 256 && i <= 31)
				{
					out << "[control char]" << i << ";";
				}
				else
				{
					// Make sure that semicolons and quotes are handled
					if (alphabet[i] == (char)59)
					{
						out << "\" ' \";";
					}
					else
					{
						out << "' " << alphabet[i] << " '" << ";";
					}

				}			

				out << success_per_char[i] << ";" << failure_per_char[i] << std::endl;

				if (i == 0)
				{
					out << ";" << comparisons;
				}
			}
		}
}


bool datacollector::counted_equal(char const a, char const b)
{
	comparisons++;
	a == b ? log_success(a) : log_failure(a);
	return a == b;
}