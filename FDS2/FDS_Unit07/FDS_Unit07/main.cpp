#include "storage.h"
#include<iostream>

void storagetest();

/*void main()
{
	storagetest();
}*/

void storagetest()
{
	storage_t s = storage_t(3);
	s.at(0) = 3;
	s.at(1) = 2;
	s.at(2) = 1;
	s.at(3) = 4;
	std::cout << s.at(0);
}