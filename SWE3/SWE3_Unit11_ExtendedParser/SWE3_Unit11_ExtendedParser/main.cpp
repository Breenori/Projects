#include <iostream>
#include "st_node.h"
#include "syntax_tree.h"

using namespace xpr;

void main()
{
	StNodeOperator<double>* op = new StNodeOperator<double>(StNodeOperator<double>::Operator::DIV);
	StNodeValue<double>* l = new StNodeValue<double>(1);
	StNodeValue<double>* r = new StNodeValue<double>(2);

	op->set_left(l);
	op->set_right(r);

	SyntaxTree<double>* tree = new SyntaxTree<double>(op);
	std::cout << "Addition: " << tree->evaluate() << std::endl;
	std::cout << tree << std::endl;
}