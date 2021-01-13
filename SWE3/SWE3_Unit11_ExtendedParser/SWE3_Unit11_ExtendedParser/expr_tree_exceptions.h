#ifndef EXPR_TREE_EXCEPTIONS_H
#define EXPR_TREE_EXCEPTIONS_H
#include<exception>

namespace xpr {

	class EvaluationException : public std::exception {
	public:
		virtual const char* what() const noexcept
		{
			return "Evaluation Exception: cannot evaluate expression tree \n";
		}
	};

}

#endif