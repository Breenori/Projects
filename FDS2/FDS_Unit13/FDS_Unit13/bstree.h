#ifndef BSTREE_H
#define BSTREE_H

class bstree {
public:
	typedef int value_t;
	bool contains(value_t const value);
private:
	struct node_t {
		value_t payload;
		node_t* left;
		node_t* right;
	};
	node_t* p_root;
	bool contains_worker(value_t const value, node_t* const& node);
};

#endif