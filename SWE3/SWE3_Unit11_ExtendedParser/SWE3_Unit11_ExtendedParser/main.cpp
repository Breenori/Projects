#include <iostream>
#include "syntax_tree.h"

using namespace xpr;

void main()
{
	StNodeOperator<double>* op = new StNodeOperator<double>(StNodeOperator<double>::Operator::ADD);
	StNodeValue<double>* l = new StNodeValue<double>(1);
	//StNodeValue<double>* r = new StNodeValue<double>(2);
	StNode<double>* r = new StNodeIdent<double>("d");

	op->set_left(l);
	op->set_right(r);

	// define tree for variable x
	StNode<double>* x = new StNodeValue<double>(42);
	SyntaxTree<double>* x_tree = new SyntaxTree<double>(x);

	NameList<SyntaxTree<double>*>* nl = new NameListMap<SyntaxTree<double>*>();
	nl->register_variable("x", x_tree);

	SyntaxTree<double>* tree = new SyntaxTree<double>(op);
	std::cout << "Addition: " << tree->evaluate(nl) << std::endl;
	std::cout << tree << std::endl;
}