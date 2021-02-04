#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H
#include "st_node.h"
#include "expr_tree_exceptions.h"
#include <iostream>

namespace xpr
{
	template<typename T>
	class SyntaxTree
	{
	public:
		SyntaxTree(StNode<T>* root) : root(root)
		{

		}

		~SyntaxTree()
		{
			if (root != nullptr)
			{
				delete root;
			}
		}

		T evaluate(NameList<SyntaxTree<T>*>* name_list)
		{
			if (root == nullptr)
			{
				throw EvaluationException();
			}
			// delegate to st_node.evaluate
			return root->evaluate(name_list);
		}

		friend std::ostream& operator<<(std::ostream& lhs, const SyntaxTree<T>* other)
		{
			other->print(lhs);
			return lhs;
		}

		// Recursive function to print trees vertically
		void print_tree(std::ostream& os, std::string const& name) const
		{
			os << "Printing tree for variable '" + name + "':\n";
			print_tree_worker(root, 0, os);
		}
		void print_tree_worker(StNode<T>* const& node, size_t const depth, std::ostream& os) const
		{
			if (node == nullptr)
			{
				return;
			}

			print_tree_worker(node->get_right(), depth+1, os);
			for (size_t n(0); n < depth; n++)
			{
				os << "  ";
			}
			
			node->print(os); os << std::endl;
			print_tree_worker(node->get_left(), depth+1, os);
		}

	private:
		StNode<T>* root;
		// Prints the tree on one line
		void print(std::ostream& os) const
		{
			if (root == nullptr)
			{
				throw EvaluationException();
			}
			else
			{
				os << "Print tree in pre-order: ";
				root->print_pre_order(os);
				os << "\n";

				os << "Print tree in in-order: ";
				root->print_in_order(os);
				os << "\n";

				os << "Print tree in post-order: ";
				root->print_post_order(os);
				os << "\n";
			}
		}
	};
}

#endif