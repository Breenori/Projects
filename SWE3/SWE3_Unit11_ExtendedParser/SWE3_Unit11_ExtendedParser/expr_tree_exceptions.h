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

	class VariableNotFoundException : public std::exception {
	private:
		std::string message;
	public:
		VariableNotFoundException(std::string message) : message(message)
		{

		}

		virtual const char* what() const noexcept
		{
			return message.c_str();
		}

	};

	class ParseException : public std::exception {
	private:
		std::string message;
	public:
		ParseException(std::string message) : message(message)
		{

		}

		virtual const char* what() const noexcept
		{
			return message.c_str();
		}

	};
}

#endif