#include "bstree.h"

bool bstree::contains(value_t const value)
{
	return contains_worker(value, p_root);
}

bool bstree::contains_worker(value_t const value, node_t* const& node)
{
	if (node == nullptr)
	{
		return false;
	}
	else if (node != nullptr)
	{
		if (node->payload == value)
		{
			return true;
		}
		else
		{
			if (value <= node->payload)
			{
				return contains_worker(value, node->left);
			}
			else
			{
				return contains_worker(value, node->right);
			}
		}
	}
	
}
