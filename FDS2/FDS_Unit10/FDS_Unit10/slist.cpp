#include "slist.h"

slist_t::slist_t()
{
	root = nullptr;
}

void slist_t::push_back(int const x)
{
	node_t* root_ref = root;
	if (root_ref != nullptr)
	{
		while (root_ref->next != nullptr)
		{
			root_ref = root_ref->next;
		}

		node_t* newnode = new node_t{ x, nullptr };

		root_ref->next = newnode;
	}
	else
	{
		root = new node_t{ x, nullptr };
	}
}

void slist_t::print_bigger_than(int const x, std::ostream& out)
{
	print_bigger_than_wrapper(root, x, out);
}

void slist_t::print_bigger_than_wrapper(node_t* node, int const x, std::ostream& out)
{
	if (node != nullptr)
	{
		if (node->data > x)
		{
			out << node->data << " ";
		}
		print_bigger_than_wrapper(node->next, x, out);
	}
}