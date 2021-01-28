#include "bf_search.h"
#include "bm_searcher.h"
#include<iostream>

void main()
{
	bm_searcher::result_type result(bm_searcher::match("anabellmagananas", "ananas"));
	std::cout << "Number of comparisons: " << result.second << std::endl;
	if (result.first == bm_searcher::NOT_FOUND)
	{
		std::cout << "Not found" << std::endl;
	}
	else
	{
		std::cout << "found at position: " << result.first << std::endl;
	}
}