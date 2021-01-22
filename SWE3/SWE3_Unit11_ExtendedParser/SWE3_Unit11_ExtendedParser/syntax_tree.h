#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H
#include "st_node.h"
#include "expr_tree_exceptions.h"
#include <iostream>
#include "name_list.h"

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
			return root->evaluate(name_list);
		}

		friend std::ostream& operator<<(std::ostream& lhs, const SyntaxTree<T>* other)
		{
			other->print(lhs);
			return lhs;
		}

	private:
		StNode<T>* root;
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