#ifndef STATISTICS_H
#define STATISTICS_H

#include<iostream>
#include<string>
#include<map>
#include<vector>

#include "animal.h"

class Statistics
{
private:
	std::map < std::string, size_t> nutrition_stats;

public:
	void print_nutrition_stats(std::vector<animals::Animal*> animals);
};

#endif
