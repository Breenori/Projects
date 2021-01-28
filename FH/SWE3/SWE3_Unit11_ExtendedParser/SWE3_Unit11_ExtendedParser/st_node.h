#ifndef ST_NODE_H
#define ST_NODE_H
#include<iostream>
#include "expr_tree_exceptions.h"
#include "string"
#include <cmath>
#include "name_list.h"
#include "syntax_tree.h"

namespace xpr {

	// forward declaration
	template<typename T>
	class SyntaxTree;

	template<typename T>
	class StNode
	{
	public:
		StNode() : left(nullptr), right(nullptr)
		{

		}
		virtual ~StNode()
		{
			if (left != nullptr)
				delete left;
			if (right != nullptr)
				delete right;
		}

		StNode<T> const* get_left() const {
			return left;
		}
		StNode<T> const* get_right() const {
			return right;
		}

		void set_left(StNode<T>* left)
		{
			this->left = left;
		}
		void set_right(StNode<T>* right)
		{
			this->right = right;
		}

		void print_in_order(std::ostream& os) const
		{
			if (left != nullptr)
			{
				left->print_in_order(os);
			}

			print(os);

			if (right != nullptr)
			{
				right->print_in_order(os);
			}
		}

		void print_pre_order(std::ostream& os) const
		{
			print(os);
			if (left != nullptr)
			{
				left->print_pre_order(os);
			}
			if (right != nullptr)
			{
				right->print_pre_order(os);
			}
		}

		void print_post_order(std::ostream& os) const
		{
			if (left != nullptr)
			{
				left->print_post_order(os);
			}
			if (right != nullptr)
			{
				right->print_post_order(os);
			}
			print(os);
		}

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const = 0;
		virtual void print(std::ostream& os) const = 0;

	protected:
		StNode<T>* left{ nullptr };
		StNode<T>* right{ nullptr };
	};

	template<typename T>
	class StNodeValue : public StNode<T>
	{
	public:
		StNodeValue(const T& value) : value(value)
		{

		}

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const override
		{
			return value;
		}

		virtual void print(std::ostream& os) const override
		{
			os << value << " ";
		}

	private:
		T value;
	};

	template<typename T>
	class StNodeOperator : public StNode<T>
	{
	public:
		enum Operator { ADD = 0, SUB, MUL, DIV, EXP };
		const std::string operator_rep[5] = { "+","-","*","/","^" };

		StNodeOperator(Operator op) : op(op) {}

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const override
		{
			StNode<T>* l{ this->left };
			StNode<T>* r{ this->right };

			switch (op)
			{
			case ADD:
				return l->evaluate(name_list) + r->evaluate(name_list);
				break;
			case SUB:
				return l->evaluate(name_list) - r->evaluate(name_list);
				break;
			case MUL:
				return l->evaluate(name_list) * r->evaluate(name_list);
				break;
			case DIV:
				return l->evaluate(name_list) / r->evaluate(name_list);
				break;
			case EXP:
				return std::pow(l->evaluate(name_list), r->evaluate(name_list));
				break;
			default:
				throw EvaluationException();
				break;
			}
		}
		virtual void print(std::ostream& os) const override
		{
			os << operator_rep[op] << " ";
		}

	private:
		Operator op;
	};

	template<typename T>
	class StNodeIdent : public StNode<T>
	{
	private:
		std::string value;
	public:
		StNodeIdent(const std::string& value) : value(value)
		{

		}

		virtual T evaluate(NameList<SyntaxTree<T>*>* name_list) const override
		{
			SyntaxTree<T>* tree = name_list->lookup_variable(value);
			if (tree != nullptr)
			{
				return tree->evaluate(name_list);
			}
			throw VariableNotFoundException("Variable: " + value + " was not defined.");
		}

		virtual void print(std::ostream& os) const override
		{
			os << value << " ";
		}
	};
}

#endif