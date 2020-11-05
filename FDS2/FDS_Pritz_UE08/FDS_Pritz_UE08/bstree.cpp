#include "bstree.h"
#include<iomanip>
#include<string>

bstree::bstree()
{
	p_root = nullptr;
	cur_size = 0;
}
bstree::bstree(bstree const& src) : bstree()
{
	copy_worker(src.p_root);
}
bstree::~bstree()
{
	clear();
}
void bstree::copy_worker(node_t* const& node)
{
	if (node != nullptr)
	{
		insert(node->payload);
		copy_worker(node->left);
		copy_worker(node->right);
	}
}

void bstree::apply(function_t f)
{
	// Delegate to the worker function
	apply_worker(f, p_root);
}
void bstree::apply_worker(function_t f, node_t* const& node)
{
	// Insert the node and then traverse all left and right nodes and also insert them recursively
	if (node != nullptr)
	{
		f(node->payload);
		apply_worker(f, node->left);
		apply_worker(f, node->right);
	}
}

bool bstree::at(std::size_t n, value_t& value)
{
	// the node with index n in our case is:
	// the n-th smallest node. (0 = most left, n=size-1 = most right)
	if (n < cur_size)
	{
		size_t counter(0);
		return at_worker(n, value, p_root, counter);
	}
	else
	{
		// if index is out of bounds, return false.
		return false;
	}
}
bool bstree::at_worker(std::size_t const n, value_t& value, node_t* const& node, size_t& counter)
{
	if (node != nullptr)
	{
		// Search left side first (smallest nodes)
		if (at_worker(n, value, node->left, counter))
		{
			return true;
		}
		else
		{
			if (counter == n)
			{
				value = node->payload;
				return true;
			}
			counter++;

			// If it isnt left, search for it right.
			if (at_worker(n, value, node->right, counter))
			{
				return true;
			}
		}
	}
	else
	{
		return false;
	}
}

size_t bstree::clear()
{
	// Delegate to the recursive worker and save its return value
	size_t deleted(clear_worker(p_root));

	// After that, the p_root should be empty. therefor it needs to be set to null.
	if (p_root != nullptr)
	{
		delete p_root;
		p_root = nullptr;
	}
	cur_size = 0;
	return deleted;
}
size_t bstree::clear_worker(node_t* const& node)
{
	if (node == nullptr)
	{
		return 0;
	}
	else
	{
		// Delete child nodes first, save their return values and return the values + 1 (for the current node)
		size_t tmp_deleted(0);
		tmp_deleted += clear_worker(node->left);
		delete node->left;
		tmp_deleted += clear_worker(node->right);
		delete node->right;
		return tmp_deleted+1;
	}
}


void bstree::insert(value_t const& value)
{
	// If the tree is uninitialized, we need to create p_root
	if (p_root == nullptr)
	{
		p_root = new node_t{ value, nullptr, nullptr };
	}
	// Else delegate to worker.
	else
	{
		insert_worker(value, p_root);
	}
	cur_size++;
}
void bstree::insert_worker(value_t const& value, node_t* const& node)
{
	if (node != nullptr)
	{
		// If the right location has been found we create a node and insert it.
		if (node->left == nullptr && value <= node->payload)
		{
			node_t* new_node = new node_t{ value, nullptr, nullptr };
			node->left = new_node;
		}
		else if (node->right == nullptr && value > node->payload)
		{
			node_t* new_node = new node_t{ value, nullptr, nullptr };
			node->right = new_node;
		}
		// Search right location by going left if current node is greater/equal and going right if current value is less than the value to be inserted.
		else if (node->left != nullptr && value <= node->payload)
		{
			insert_worker(value, node->left);
		}
		else if (node->right != nullptr && value > node->payload)
		{
			insert_worker(value, node->right);
		}
	}
}

bool bstree::remove(value_t const& value)
{
	// If the node to be removed is the root
	if (p_root != nullptr && p_root->payload == value)
	{
		// temporarily backup the old root
		node_t* old_root = p_root;
		cur_size--;

		// if the root node is the only node, delete it and set it to null.
		if (p_root->left == nullptr && p_root->right == nullptr)
		{
			delete p_root;
			p_root = nullptr;
			return true;
		}
		// If one side isn't null, set either left or right pointer as new root and insert all the elements on the other side node by node.
		else if (p_root->left != nullptr)
		{
			p_root = p_root->left;
			reinsert_subtree(old_root->right);
			if (old_root->right != nullptr)
			{
				delete old_root->right;
			}
			delete old_root;
			return true;
		}
		else if (p_root->right != nullptr)
		{
			p_root = p_root->right;
			reinsert_subtree(old_root->left);
			if (old_root->left != nullptr)
			{
				delete old_root->left;
			}
			delete old_root;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		// If its another node, we delegate to the worker function
		return remove_worker(value, p_root);
	}
}
bool bstree::remove_worker(value_t const& value, node_t* const& node)
{
	if (node == nullptr)
	{
		// Recursion floor
		return false;
	}
	// If left node is the value to be deleted:
	else if (node->left != nullptr && node->left->payload == value)
	{
		// Backup the node
		node_t* to_be_deleted = node->left;

		// If the node to be removed has successors we need to save access to them
		// I decided to let one successor replace the node and then reattach the other successor in a fitting location
		if (node->left->right != nullptr)
		{
			node->left = node->left->right;
			reinsert_subtree(to_be_deleted->left);
			if (to_be_deleted->left != nullptr)
			{
				delete to_be_deleted->left;
			}
		}
		else if (node->left->left != nullptr)
		{
			node->left = node->left->left;
			reinsert_subtree(to_be_deleted->right);
			if (to_be_deleted->right != nullptr)
			{
				delete to_be_deleted->right;
			}
		}
		else
		{
			delete node->left;
			node->left = nullptr;
			to_be_deleted = nullptr;
		}

		// Then delete the backup pointer, set it to null and reduce the size.
		if (to_be_deleted != nullptr)
		{
			delete to_be_deleted;
			to_be_deleted = nullptr;
		}
		cur_size--;
		return true;
	}
	else if (node->right != nullptr && node->right->payload == value)
	{
		// Same as above. Backup the node, then replace and reattach nodes.
		node_t* to_be_deleted = node->right;

		if (node->right->right != nullptr)
		{
			node->right = node->right->right;
			reinsert_subtree(to_be_deleted->left);
			if (to_be_deleted->left != nullptr)
			{
				delete to_be_deleted->left;
			}
		}
		else if (node->right->left != nullptr)
		{
			node->right = node->right->left;
			reinsert_subtree(to_be_deleted->right);
			if (to_be_deleted->right != nullptr)
			{
				delete to_be_deleted->right;
			}
		}
		else
		{
			delete node->right;
			node->right = nullptr;
			to_be_deleted = nullptr;
		}

		if (to_be_deleted != nullptr)
		{
			delete to_be_deleted;
		}
		cur_size--;
		return true;
	}
	else
	{
		// As long as the element hasnt found, traverse recursively
		if (node->left != nullptr && value < node->payload)
		{
			return remove_worker(value, node->left);
		}
		else if (node->right != nullptr && value > node->payload)
		{
			return remove_worker(value, node->right);
		}
	}
}
size_t bstree::remove_all(value_t const& value)
{
	// Delete as long as the element could be found and return the amount off occurences.
	size_t removed(0);
	while (remove(value))
	{
		removed++;
	}
	return removed;
}


size_t bstree::count(value_t const& value) const
{
	return count_worker(value, p_root);
}
size_t bstree::count_worker(value_t const& value, node_t* const& node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	else
	{
		// Traverse the tree based on size: Search smaller elements (than the current node) left, bigger ones right.
		if (value < node->payload)
		{
			return count_worker(value, node->left);
		}
		else if (value > node->payload)
		{
			return count_worker(value, node->right);
		}
		else
		{
			// If we find it we add up.
			return count_worker(value, node->left) + 1;
		}
	}
}

size_t bstree::size() const
{
	return cur_size;
}
bool bstree::empty() const
{
	// If the p_root is null the list is empty.
	return p_root == nullptr;
}

bool bstree::equals(bstree const& rhs) const
{
	return equals_worker(p_root, rhs.p_root);
}
bool bstree::equals_worker(node_t* const& lhs, node_t* const& rhs) const
{
	if (lhs == nullptr && rhs == nullptr)
	{
		return true;
	}
	else if (lhs != nullptr && rhs == nullptr || lhs == nullptr && rhs != nullptr)
	{
		return false;
	}
	else
	{
		return equals_worker(lhs->left, rhs->left) && equals_worker(lhs->right, rhs->right) && lhs->payload == rhs->payload;
	}
}

bool bstree::contains(value_t const& value) const
{
	return contains_worker(value, p_root);
}
bool bstree::contains_worker(value_t const& value, node_t* const& node) const
{
	if (node == nullptr)
	{
		return false;
	}
	else if (node->payload == value)
	{
		return true;
	}
	else
	{
		if (node->payload > value)
		{
			return contains_worker(value, node->left);
		}
		else
		{
			return contains_worker(value, node->right);
		}
	}
}

void bstree::reinsert_subtree(node_t* const& subtree)
{
	// Insert all nodes from the subtree.
	// All the nodes had been inserted before, which is why we need to balance cur_size by substracting one on every insert.
	if (subtree != nullptr)
	{
		insert(subtree->payload);
		cur_size--;
		reinsert_subtree(subtree->left);
		reinsert_subtree(subtree->right);
		if (subtree->left != nullptr)
		{
			delete subtree->left;
		}
		if (subtree->right != nullptr)
		{
			delete subtree->right;
		}
	}
}

std::ostream& bstree::print(std::ostream& out) const
{
	out << "< ";
	size_t count(0);
	print_worker(p_root, count, out);
	out << " >\n";
	return out;
}
void bstree::print_worker(node_t* const& node, size_t& counter, std::ostream& out) const
{
	// Recursively print every number from smallest to largest.
	if (node != nullptr)
	{
		// Left = smallest. Print them first. 
		print_worker(node->left, counter);
		// To detect first number we need a referenced variable
		if (counter > 0)
		{
			out << ", ";
		}
		// After left, print parent, then right child
		out << node->payload;
		counter++;
		print_worker(node->right, counter);
	}
}

std::ostream& bstree::print_2d(std::ostream& out) const
{
	print_2d_worker(p_root, 0, get_max_depth(), out);
	return out;
}
void bstree::print_2d_worker(node_t* const& node, size_t const depth, size_t const max_depth, std::ostream& out) const
{
	if (node != nullptr)
	{
		// Since it's turned 90 degrees, we need to start with the furthest right node this time.
		print_2d_worker(node->right, depth + 1, max_depth, out);
		// Print the node with variable indention
		out << std::setw(depth * indention) << node->payload << std::endl;
		print_2d_worker(node->left, depth + 1, max_depth, out);
	}
	else
	{
		if (depth <= max_depth)
		{
			// If a node is missing, we need to print empty lines (the higher the difference to max_depth, the more lines)
			// Doing this will always result in a indentions similiar to a balanced tree
			for (size_t n(0); n < max_depth - depth; n++)
			{
				out << std::endl;
			}
		}
	}
}

std::ostream& bstree::print_2d_upright(std::ostream& out) const
{
	print_2d_upright_worker(p_root, out);
	return out;
}
void bstree::print_2d_upright_worker(node_t* const& node, std::ostream& out) const
{
	size_t max_depth(get_max_depth());
	// Print each line (all values for the specified depth)
	for (size_t i(0); i <= max_depth; i++)
	{
		out << std::setw(i) << "";
		print_elements_of_depth(p_root, 0, i, out);
		out << std::endl;
	}
}
void bstree::print_elements_of_depth(node_t* const& node, size_t const depth, size_t const target_depth, std::ostream& out) const
{
	// Regarding the formula for the width:
	// I couldn't find anything. I thought having <totalspace>/<amount of spaces> would work, but it didn't.
	// Therefor i just used "trial and error" and this seemed to work for most widths. For whatever reason.
	size_t width(((upright_width - target_depth * (upright_width / 40)) / (pow(2, target_depth) + 1)));

	if (node != nullptr)
	{
		// If the required depth has been reached, dont go deeper and print the payload.
		if (depth == target_depth)
		{
			out << std::setw(width) << node->payload;
		}
		else
		{
			// Traverse down to reach required depth.
			print_elements_of_depth(node->left, depth + 1, target_depth, out);
			print_elements_of_depth(node->right, depth + 1, target_depth, out);
		}
	}
	else
	{
		// If value is null, print blanks and placehorders according to current height.
		for (int i(0); i < pow(2, target_depth - depth); i++)
		{
			out << std::setw(width) << "*";
		}
	}
}

size_t bstree::get_max_depth() const
{
	size_t depth(0);
	get_max_depth_worker(p_root, 0, depth);
	return depth;
}
void bstree::get_max_depth_worker(node_t* const& node, size_t const depth, size_t& max_depth) const
{
	if (node != nullptr)
	{
		// Determine max depth by going through all nodes and setting the reference parameter to a new maximum.
		if (depth > max_depth)
		{
			max_depth = depth;
		}
		get_max_depth_worker(node->left, depth + 1, max_depth);
		get_max_depth_worker(node->right, depth + 1, max_depth);
	}
}