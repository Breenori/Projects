#include "slist.h"
#include<cassert>

//Public
slist::slist()
{
	p_root = nullptr;
	listsize = 0;
	sorted = true;
}

slist::slist(slist const& src)
{
	// When copying, we can just copy everything except the actual values.
	this->listsize = 0;
	this->sorted = true;

	// When copying the values, we need to copy them one by one.
	// Else we would link the two lists and change both at the same time.
	value_t src_val(0);
	this->p_root = nullptr;

	for (int i(0); i < src.size(); i++)
	{
		src.at(i, src_val);
		this->push_back(src_val);
	}
}

slist::~slist()
{
	// Just delegate to clear...
	clear();
}


void slist::apply(function_t f)
{
	// Apply function to every node.
	node_t* root_ref = p_root;
	while (root_ref != nullptr)
	{
		f(root_ref->data);
		root_ref = root_ref->next;
	}
}

bool slist::at(size_t n, value_t& value) const
{
	// If index <n> out of bounds, return false.
	if (n > listsize)
	{
		std::cout << "Error: Couldn't fetch element at position " << n << ".\n";
		return false;
	}
	else
	{
		// Else, go to "p_root->next" <n> times and return the data.
		node_t* root_ref(p_root);
		while (n > 0)
		{
			root_ref = root_ref->next;
			n--;
		}

		value = root_ref->data;
		return true;
	}
}

size_t slist::clear()
{
	// Reset attributes to default
	listsize = 0;
	sorted = true;
	size_t amount_deleted(0);

	// If list is not empty, recursively delete all elements using the wrapper.
	// Afterwards, root can be set to nullpointer.
	if (p_root != nullptr)
	{
		amount_deleted = clear_helper(p_root);
		p_root = nullptr;
	}

	return amount_deleted;
}
// Private, but placed here for better overview
size_t slist::clear_helper(node_t* node)
{
	// if there is a next node, call it.
	// When unwinding, delete the nodes (beginning from the back).
	if (node != nullptr)
	{
		size_t tmp = clear_helper(node->next) + 1;
		delete[] node;
		return tmp;
	}
}

bool slist::contains(value_t const& value) const
{
	return count(value) > 0;
}

size_t slist::count(value_t const& value) const
{
	value_t cur_val(0);
	size_t counter(0);

	// Check for all elements if they're equal to <value> and similiarties.
	for (int n(0); n < listsize; n++)
	{
		at(n, cur_val);
		if (cur_val == value)
		{
			counter++;
		}
	}

	return counter;
}

bool slist::empty() const
{
	return listsize == 0;
}

bool slist::equal(slist const& rhs) const
{
	// If listsizes are the same, we need to compare the values.
	if (listsize == rhs.listsize)
	{
		bool flag(true);

		value_t lhs_val;
		value_t rhs_val;

		size_t n(0);
		// If every single element is the same on the other list, then the lists are the same.
		while (n < listsize && flag)
		{
			at(n, lhs_val);
			rhs.at(n, rhs_val);

			if (lhs_val != rhs_val)
			{
				flag = false;
			}
			n++;
		}

		return flag;
	}
	else
	{
		return false;
	}
}

void slist::insert_sorted(value_t const& value)
{
	// If the list is empty, just put it at the start.
	if (p_root == nullptr)
	{
		p_root = new node_t{ value, nullptr };
	}
	else
	{
		// If the list is not sorted, sort it first.
		if (!sorted)
		{
			sort();
		}

		// If the first value is greater than <value>, let value become the new root and attach old root as "p_root->next"
		if (p_root->data > value)
		{
			node_t* new_node = new node_t{ value, p_root };
			p_root = new_node;
		}
		else
		{
			node_t* root_ref(p_root);
			// Go to next element as long as it's data is less than <value>
			while (root_ref->next != nullptr && value > root_ref->next->data)
			{
				root_ref = root_ref->next;
			}

			// If we aren't at the end of the list by now, place the new element in front of the next element (which is bigger).
			// -> Attach the current "next"-pointer to the new node with <value> and attach it to the existing list.
			if (root_ref->next != nullptr)
			{
				node_t* next_node = new node_t{ value, root_ref->next };
				root_ref->next = next_node;
			}
			// If all elements are less and we are at the end, just attach it.
			else
			{
				root_ref->next = new node_t{ value, nullptr };
			}
		}
	}

	// Increase listsize to avoid counting it everytime...
	listsize++;
}

bool slist::pop_back(value_t& value)
{
	// If the list is empty, we can't return an element.
	if (p_root == nullptr)
	{
		std::cout << "Error: Couldn't fetch last element. List is empty.\n";
		return false;
	}
	else
	{
		// if there is only one element, return the data, delete the node and set root to nullptr since its now empty.
		if (listsize == 1)
		{
			value = p_root->data;
			delete[] p_root;
			p_root = nullptr;
		}
		// If the list contains more than one element, return the element and set the previous elements "next"-pointer to a nullptr to become the last element.
		else
		{
			node_t* root_ref(p_root);
			while (root_ref->next->next != nullptr)
			{
				root_ref = root_ref->next;
			}

			value = root_ref->next->data;
			delete[] root_ref->next;
			root_ref->next = nullptr;
		}
		listsize--;
		return true;
	}
}

bool slist::pop_front(value_t& value)
{
	// If list is empty we cant return a value.
	if (p_root == nullptr)
	{
		std::cout << "Error: Couldn't fetch first element. List is empty.\n";
		return false;
	}
	else
	{
		// If the list has one element, return its value, delete it and set root to nullptr since its empty.
		if (listsize == 1)
		{
			value = p_root->data;
			delete p_root;
			p_root = nullptr;
		}
		// If it has more elements, the 2nd element needs to become the new root.
		else
		{
			value = p_root->data;
			node_t* next = p_root->next;

			delete[] p_root;
			p_root = next;

		}
		listsize--;
		return true;
	}

}

std::ostream& slist::print(std::ostream& out) const
{
	if (p_root != nullptr)
	{
		node_t* root_ref(p_root);

		// Loop through all nodes and print their data component.
		for (size_t n(0); n < listsize; n++)
		{
			if (n >= 1)
			{
				out << ", ";
			}
			out << root_ref->data;
			root_ref = root_ref->next;
		}

		out << std::endl;
	}
	else
	{
		out << "The list is empty.\n";
	}
	return out;
}



std::ostream& slist::print_reverse(std::ostream& out) const
{
	// If root is a nullpointer we can't print anything
	if (p_root == nullptr)
	{
		out << "This list is empty." << std::endl;
	}
	else
	{
		// Else, delegate to wrapper.
		print_reverse_helper(p_root, out);
		out << std::endl;
		return out;
	}
}
// Private, but placed here for better overview
std::ostream& slist::print_reverse_helper(node_t* const& node, std::ostream& out) const
{
	// Recursion floor: node is nullpointer (do nothing)
	if (node != nullptr)
	{
		// Call recursive function
		print_reverse_helper(node->next, out);

		// Upon unwinding, print the values (starting from the back!)
		out << node->data;

		// Print a comma after every node til root.
		if (node != p_root)
		{
			out << ", ";
		}
		return out;
	}
}


void slist::reverse()
{
	// If the list is empty or of size 1 reversing it is pointless.
	if (p_root != nullptr && listsize != 1)
	{
		p_root = reverse_helper(p_root);
	}
	else
	{
		std::cout << "List is empty or size one. Skipping unmeaningful reversal process.\n";
	}
}
// Private, but placed here for better overview
slist::node_t* slist::reverse_helper(node_t*& cur_node)
{
	// Recursion floor: node->next is null. We return the last node since it becomes the new head (by unwinding it will be returned til the start)
	if (cur_node->next == nullptr)
	{
		return cur_node;
	}

	if (cur_node->next != nullptr)
	{
		// Call recursive function
		node_t* returnval(reverse_helper(cur_node->next));

		// Upon unwinding, set the "next" pointer of the next node, to a pointer to the current node.
		cur_node->next->next = cur_node;

		// ... except it's the root node. Then, set it's next node to null.
		if (cur_node == p_root)
		{
			cur_node->next = nullptr;
		}

		// Keep returning the last node (new head)!
		return returnval;
	}
}



void slist::push_back(value_t const& value)
{
	// If the list is empty, create a new node and make it root.
	if (p_root == nullptr)
	{
		p_root = new node_t{ value, nullptr };
	}
	// If the list isn't empty, loop as long as "next" isn't a nullpointer and attach it there.
	else
	{
		node_t* root_ref(p_root);
		while (root_ref->next != nullptr)
		{
			root_ref = root_ref->next;
		}

		root_ref->next = new node_t{ value, nullptr };
	}
	listsize++;

	// By inserting using this method, we don't guarantee that it's still sorted. Set it to false.
	if (sorted)
	{
		sorted = false;
	}
}

void slist::push_front(value_t const& value)
{
	// if the list is empty, create a new node and make it p_root
	if (p_root == nullptr)
	{
		p_root = new node_t{ value, nullptr };
	}
	// If it isn't empty, create a new node, set p_root as the "next"-pointer and become p_root.
	else
	{
		node_t* new_node = new node_t{ value, p_root };
		p_root = new_node;
	}
	listsize++;

	// By inserting using this method, we don't guarantee that it's still sorted. Set it to false.
	if (sorted)
	{
		sorted = false;
	}
}

size_t slist::remove_all(value_t const& value)
{
	// If the list is empty we can't remove anything.
	if (p_root == nullptr)
	{
		return 0;
	}
	else
	{
		size_t counter(0);

		// As long as the root node stores the value, make "next" the new root_node.
		while (p_root->data == value)
		{
			node_t* next = p_root->next;
			delete[] p_root;
			p_root = next;
			listsize--;
			counter++;
		}

		// For all further connections, the NEXT node is being compared to the value 
		// (since we need to modify the "next" - pointer of the node PRIOR to it, which we don't have access to afterwards) 
		node_t * root_ref = p_root;
		while (root_ref->next != nullptr)
		{
			if (root_ref->next->data == value)
			{
				node_t* next = root_ref->next->next;
				delete[] root_ref->next;
				root_ref->next = next;
				listsize--;
				counter++;
			}
			else
			{
				root_ref = root_ref->next;
			}
		}


		return counter;
	}
}

size_t slist::size() const
{
	// Return listsize instead of counting it over and over again :)
	return listsize;
}

void slist::sort()
{
	// Convert to carray first, so we don't have to go through all the values everytime.
	// e.g. list with 100 elements needs 100 cycles of a while loop (following the pointer) to get the last element.
	value_t* help_array = to_carray();

	// Sort the carray
	for (size_t i(0); i < listsize - 1; i++)
	{
		size_t k = i;
		for (size_t j(k); j < listsize; j++)
		{
			if (help_array[j] < help_array[k])
			{
				k = j;
			}
		}
		std::swap(help_array[i], help_array[k]);
	}

	// Set the values of the carray to the corresponding places in the slist.
	for (size_t i(0); i < listsize; i++)
	{
		at(i) = help_array[i];
	}

	// Dont forget to free the carrays memory
	delete[] help_array;
	sorted = true;
}





//Private
slist::value_t* slist::to_carray()
{
	if (p_root != nullptr)
	{
		value_t* list_as_array = new value_t[listsize];
		node_t* root_ref = p_root;

		for (int n(0); n < listsize; n++)
		{
			list_as_array[n] = root_ref->data;
			root_ref = root_ref->next;
		}

		return list_as_array;
	}
	return nullptr;
}

slist::value_t& slist::at(size_t n)
{
	if (p_root != nullptr)
	{
		n = n % listsize;

		node_t* root_ref(p_root);
		while (n > 0)
		{
			root_ref = root_ref->next;
			n--;
		}

		return root_ref->data;
	}
	else
	{
		std::cout << "Warning: There are no elements.\n";
		assert("User accessing private function wanted to access empty list. Can't return reference." && false);
	}
}


