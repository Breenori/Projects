#ifndef SLIST_H
#define SLIST_H
#include<iostream>

struct node_t {
	int data;
	node_t* next;
};

class slist_t {
public:
	slist_t();
	void push_back(int const x);
	void print_bigger_than(int const x, std::ostream& out = std::cout);
private:
	node_t * root;
	void print_bigger_than_wrapper(node_t* node, int const x, std::ostream& out = std::cout);
};

#endif