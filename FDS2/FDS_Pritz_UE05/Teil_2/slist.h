#ifndef SLIST_H
#define SLIST_H
#include<iostream>

class slist {
public:
	typedef size_t value_t;
	typedef void (*function_t) (value_t&);

	// Default constructor: Creates an empty singly linked list (slist)
	slist();
	// Constructor: Copies the given slist <src>s data to create a new slist.
	slist(slist const& src);
	// Destructor: Delegates to clear().
	~slist();

	// Applies function <f> to every single node
	void apply(function_t f);
	// Returns whether the index <n> is within bounds and if true returns the element via <value>
	bool at(size_t n, value_t& value) const;
	// Removes all entries from the list, frees dynamically allocated memory and resets attributes to default (size, sorted...)
	// Returns the amount of removed entries.
	size_t clear();
	// Returns whether the list contains the given element <value> or not.
	bool contains(value_t const& value) const;
	// Returns how often the given element <value> is inside the slist.
	size_t count(value_t const& value) const;
	// Returns whether the slist is empty or not.
	bool empty() const;
	// Returns whether the list is equal to another slist <rhs>
	bool equal(slist const& rhs) const;
	// Inserts the given element <value> in a way to ensure it is still sorted after insertion.
	// If the list is unsorted before insertion, the list is first being sorted.
	void insert_sorted(value_t const& value);
	// Fetch and remove an element from the back of the list via <value> and return whether it was possible.
	// Returns whether it was possible. (if the list is not empty)
	bool pop_back(value_t& value);
	// Fetch and remove an element from the front of the list via <value>
	// Returns whether it was possible. (if the list is not empty)
	bool pop_front(value_t& value);
	// Prints all members of the list to the specified stream <out>
	std::ostream& print(std::ostream& out = std::cout) const;


	// Prints all members of the list to the specified stream <out> in reverse order.
	std::ostream& print_reverse(std::ostream& out = std::cout) const;

	// Reverses the order of elements
	void reverse();

	// Inserts a new element <value> at the end of the slist.
	void push_back(value_t const& value);
	// Inserts a new element <value> at the start of the slist.
	void push_front(value_t const& value);
	// Removes all entries similiar to <value> from the list.
	// Returns the number of removed entries.
	size_t remove_all(value_t const& value);
	// Returns the current size of the slist.
	size_t size() const;
	// Sorts the slist ascending.
	void sort();


private:
	struct node_t
	{
		value_t data;
		node_t* next;
	};
	
	// It's way more efficient to keep track of the listsize than to calculate it over and over.
	size_t listsize;
	node_t * p_root;
	// Instead of sorting it everytime, keeping track of the state to avoid unnecessary sorting will improve performance for insert_sorted()
	bool sorted;
	// Returns the slist as a carray
	value_t* to_carray();
	// Returns a reference to element at <n>
	value_t& at(size_t n);
	// Recursive function to clear the list, with an added node_t* parameter.
	// Returns the amount of nodes deleted.
	size_t clear_helper(node_t* node);

	// Wrapper function for print_reverse.
	std::ostream& print_reverse_helper(node_t* const& node, std::ostream& out) const;
	// Recursive function needed for reverse()
	// Returns a pointer to the new head of the list.
	node_t* reverse_helper(node_t*& cur_node);
};

#endif