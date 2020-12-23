#include "statistics.h"

using animals::Animal;

void Statistics::print_nutrition_stats(std::vector<animals::Animal*> animals)
{
	std::cout << "Printing nutrition statistics:\n";
	for (size_t i(0); i < animals.size(); ++i)
	{
		Animal& curr = *animals[i];
		nutrition_stats[curr.get_nutrition()]
			? nutrition_stats[curr.get_nutrition()]++ // nutrition category available
			: nutrition_stats[curr.get_nutrition()] = 1;
	}

	for (auto it = nutrition_stats.begin(); it != nutrition_stats.end(); ++it)
	{
		std::cout << it->first << ": " << it->second << "\n";
	}
}
