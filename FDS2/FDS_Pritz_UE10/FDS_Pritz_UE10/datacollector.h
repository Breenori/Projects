#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H
#include<vector>
#include<iostream>

class datacollector
{
private:
	size_t comparisons;
	std::vector<char> alphabet;
	std::vector<size_t> success_per_char;
	std::vector<size_t> failure_per_char;
public:
	datacollector();
	datacollector(std::vector<char> const& alphabet);
	~datacollector();
	// Initializes the vectors for storage with the desired alphabets size and characters.
	void init(std::vector<char> const& alphabet);
	// Clears all stored values.
	void reset_statistics();
	// Increases the amount of successes per char for the given character.
	void log_success(char const character);
	// Increases the amount of failures per char for the given character.
	void log_failure(char const character);
	// Returns the size of the initialized alphabet
	size_t get_alphabet_size();
	// Returns the amount of total comparisons.
	size_t get_comparison_count();
	// Returns the vector of all successful comparisons
	std::vector<size_t> get_success_statistics();
	// Returns the vector of all failed comparisons
	std::vector<size_t> get_failure_statistics();
	// Prints all relevant values to the designated outputstream in csv fashion.
	void print_statistics(std::ostream& out);
	// Returns whether a and b are equal and alters the success/failure vectors.
	bool counted_equal(char const a, char const b);
};

#endif
