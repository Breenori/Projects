#ifndef BSTREE_H
#define BSTREE_H
#include<iostream>
#include<vector>

class bstree {
public:
	typedef int value_t;
	typedef  void (*function_t) (value_t&);
	
	// Default constructor
	bstree();
	// Copy Constructor
	bstree(bstree const& src);
	// Deconstructor
	~bstree();

	// Applies a given function to every node
	void apply(function_t f);
	// Writes the n-th smallest element inside the tree to output parameter.
	// returns whether element could be written (inside bounds)
	bool at(std::size_t const n, value_t& value);
	// Removes all elements from the list and restores default values.
	size_t clear();
	// Returns whether the given value already exists in the tree.
	bool contains(value_t const& value) const;
	// Returns the number of of occurences of a given value.
	size_t count(value_t const& value) const;
	// Returns whether the tree is empty or not.
	bool empty() const;
	// Returns whether two trees are equal (same nodes)
	bool equals(bstree const& rhs) const;
	// Inserts a new node with the given value in the right position.
	void insert(value_t const& value);
	// prints the contents of the tree in array form.
	std::ostream& print(std::ostream& out = std::cout) const;
	// Prints the tree in a 90 degree turned fashion (left to right)
	std::ostream& print_2d(std::ostream& out = std::cout) const;
	// Prints the tree in a vertical manner.
	std::ostream& print_2d_upright(std::ostream& out = std::cout) const;
	// Removes a given value from the tree
	// Returns whether an element with that value could be found.
	bool remove(value_t const& value);
	// Removes all elements with the given value from the tree.
	// Returns the amount of occurences removed.
	size_t remove_all(value_t const& value);
	// returns the amount of values inside the tree.
	size_t size() const;

private:
	struct node_t {
		value_t payload;
		node_t* left;
		node_t* right;
	};
	node_t* p_root;
	size_t cur_size;
	// Values related to output/print
	size_t const upright_width = 160;
	size_t const indention = 5;

	size_t get_max_depth() const;
	void reinsert_subtree(node_t* const& subtree);

	// All worker functions for the recursive functions
	void copy_worker(node_t* const& node);
	void apply_worker(function_t f, node_t* const& node);
	void insert_worker(value_t const& value, node_t* const& node);
	bool contains_worker(value_t const& value, node_t* const& node) const;
	size_t clear_worker(node_t* const& node);
	size_t count_worker(value_t const& value, node_t* const& node) const;
	bool equals_worker(node_t* const& lhs, node_t* const& rhs) const;
	bool remove_worker(value_t const& value, node_t* const& node);
	void print_worker(node_t* const& node, size_t& counter, std::ostream& out = std::cout) const;
	void print_2d_worker(node_t* const& node, size_t const depth, size_t const max_depth, std::ostream& out = std::cout) const;
	void print_2d_upright_worker(node_t* const& node, std::ostream& out = std::cout) const;
	bool at_worker(std::size_t const n, value_t& value, node_t* const& node, size_t& counter);
	void get_max_depth_worker(node_t* const& node, size_t const depth, size_t& max_depth) const;
	void print_elements_of_depth(node_t* const& node, size_t const depth, size_t const target_depth, std::ostream& out = std::cout) const;
};

#endif