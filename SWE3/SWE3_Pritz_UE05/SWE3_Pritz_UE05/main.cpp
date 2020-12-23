#include "DateTime.h"
#include<iostream>

void main()
{
	DateTime date = DateTime();
	std::cout << date.toStr() << std::endl;

	DateTime cdate = DateTime(22, 12, 2020,0,0,0);
	std::cout << cdate.toStr() << std::endl;

	std::cout << "Difference: " << DateTime::diff(date, cdate).toStr();
}