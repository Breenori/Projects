#ifndef PARSER_H
#define PARSER_H
#include "pfc_scanner.h"
#include "syntax_tree.h"
#include "name_list.h"

namespace xpr
{
	class ParserException final : public std::runtime_error {
	public:
		explicit ParserException(std::string const& message) : std::runtime_error{ message } { }
	};

	class Parser
	{
	public:
		Parser()
		{

		}
		virtual ~Parser()
		{}
		virtual void parse() = 0;
	protected:
		pfc::scanner scanner;

		// Terminal beginnings
		bool is_tb_Expression() const
		{
			return is_tb_Term();
		}
		bool is_tb_Term() const
		{
			return is_tb_Factor();
		}
		bool is_tb_Factor() const
		{
			return is_tb_AddOp() || is_tb_UFactor();
		}
		bool is_tb_UFactor() const
		{
			return is_tb_Monom() || is_tb_PExpression();
		}
		bool is_tb_Monom() const
		{
			return is_tb_WMonom();
		}
		bool is_tb_WMonom() const
		{
			return is_tb_Unsigned() || is_tb_Identifier();
		}
		bool is_tb_Identifier() const
		{
			return scanner.is_identifier() && !scanner.is_keyword();
		}
		bool is_tb_Exponent() const
		{
			return scanner.is('^');
		}
		bool is_tb_AddOp() const
		{
			return scanner.is('+') || scanner.is('-');
		}
		bool is_tb_MultOp() const
		{
			return scanner.is('*') || scanner.is('/');
		}
		bool is_tb_PExpression() const
		{
			return scanner.is('(');
		}
		bool is_tb_Unsigned() const
		{
			return scanner.is_number();
		}


	};

	class ParseSyntaxTree : public Parser
	{
	public:
		typedef StNode<double>* node_t;
		typedef NameList<SyntaxTree<double>*>* name_t;
		ParseSyntaxTree(std::istream& in)
		{
			// register print and set as keywords (to distinguish between them and variables)
			scanner.register_keyword("print");
			scanner.register_keyword("set");
			scanner.set_istream(in);

			// Create a new namelist to store our syntaxtree variables in
			name_list = new NameListMap<SyntaxTree<double>*>();
		}

		virtual ~ParseSyntaxTree()
		{
			delete name_list;
		}

		void parse() override
		{
			parse_program();
		}

		void print_all_variables(std::ostream& os) const
		{
			name_list->print_name_list(os);
		}

	private:
		name_t name_list;

		// Additional terminal beginnings specific to our program
		bool is_tb_Program()
		{
			return is_tb_outputs() || is_tb_assignments();
		}

		bool is_tb_outputs()
		{
			return is_tb_output();
		}
		bool is_tb_output()
		{
			return scanner.is_keyword("print");
		}

		bool is_tb_assignments()
		{
			return is_tb_assignment();
		}
		bool is_tb_assignment()
		{
			return scanner.is_keyword("set");
		}

		void parse_program()
		{
			if (!is_tb_Program())
			{
				throw ParseException("Parse exception in Rule 'Program'.");
			}

			while (is_tb_Program())
			{
				if (is_tb_outputs())
				{
					parse_outputs();
				}
				else if (is_tb_assignments())
				{
					parse_assignments();
				}
			}
		}

		void parse_outputs()
		{
			if (!is_tb_outputs())
			{
				throw ParseException("Parse exception in rule 'Outputs'.");
			}

			parse_output();
			while (is_tb_outputs())
			{
				parse_output();
			}
		}
		void parse_output()
		{
			if (!is_tb_output())
			{
				throw ParseException("Parse exception in rule 'Output'.");
			}

			scanner.next_symbol("print");
			scanner.next_symbol('(');
			node_t root = parse_Expression();
			scanner.next_symbol(')');
			scanner.next_symbol(';');

			SyntaxTree<double>* st = new SyntaxTree<double>(root);
			std::cout << st->evaluate(name_list) << std::endl;
			// std::cout << st;
			delete st;
		}

		void parse_assignments()
		{
			if (!is_tb_assignments())
			{
				throw ParseException("Parse exception in rule 'Assignments'.");
			}

			parse_assignment();
			while (is_tb_assignment())
			{
				parse_assignment();
			}
		}
		void parse_assignment()
		{
			if (!is_tb_assignment())
			{
				throw ParseException("Parse exception in rule 'Assignment'.");
			}

			scanner.next_symbol("set");
			scanner.next_symbol('(');
			std::string identifier = scanner.get_identifier(); scanner.next_symbol();
			if (identifier.empty())
			{
				throw InvalidIdentifierException();
			}
			scanner.next_symbol(',');

			node_t root = parse_Expression();
			scanner.next_symbol(')');
			scanner.next_symbol(';');

			name_list->register_variable(identifier, new SyntaxTree<double>(root));
		}

		// parse functions

		// Sequence of additions/subtractions
		node_t parse_Expression()
		{
			if (!is_tb_Expression())
			{
				throw ParserException("Error parsing 'Expression'.");
			}

			// The root node needs to be created and its left child can be populated
			node_t root = nullptr;
			node_t right = nullptr;

			node_t left(parse_Term());
			if (is_tb_AddOp())
			{
				double const sign{ parse_AddOp() };
				root = (sign == 1 ? new StNodeOperator<double>(StNodeOperator<double>::Operator::ADD)
					: new StNodeOperator<double>(StNodeOperator<double>::Operator::SUB));
				root->set_left(left);
				right = parse_Term();
			}

			// We can't populate the right child yet, since it is unclear whether there are more operands/operators.
			// Thats why we save "right" for the time being.

			node_t ref = root;
			while (is_tb_AddOp())
			{
				// Everytime an AddOp appears, we create the corresponding Operator Node...
				double const sign{ parse_AddOp() };

				node_t op_node = (sign == 1 ? new StNodeOperator<double>(StNodeOperator<double>::Operator::ADD)
					: new StNodeOperator<double>(StNodeOperator<double>::Operator::SUB));
				// ...And set it as the current reference nodes (the one who is the farthest to the right) right child node.
				ref->set_right(op_node);

				// The reference node then becomes this operator node and its left child can be set to the previously parsed "right".
				ref = op_node;
				ref->set_left(right);

				// Last but not least, prepare the next "right" node.
				right = parse_Term();
			}

			// If a tree exists, append the "right" node to the bottom right node.
			if (ref != nullptr)
				ref->set_right(right);
			// Or if the tree doesn't even exist (= only one value), left becomes the root node.
			else
				root = left;


			return root;
		}

		// Sequence of multiplications/divisions
		node_t parse_Term()
		{
			if (!is_tb_Term())
			{
				throw ParserException("Error parsing 'Term'.");
			}

			// This function works analogous to "parse expression". if questions arise, consult the other function.
			node_t root = nullptr;
			node_t right = nullptr;
			node_t left(parse_Factor());
			if (is_tb_MultOp())
			{
				// Instead of parsing the AddOp, we now have to consider MultOp and create Operator Nodes accordingly
				if (scanner.is('*'))
				{
					scanner.next_symbol('*');
					root = new StNodeOperator<double>(StNodeOperator<double>::Operator::MUL);
				}
				else if (scanner.is('/'))
				{
					scanner.next_symbol('/');
					root = new StNodeOperator<double>(StNodeOperator<double>::Operator::DIV);
				}
				root->set_left(left);
				right = parse_Factor();
			}

			node_t ref = root;


			// As long as there are more operators we continue to add them to the tree
			while (is_tb_MultOp())
			{
				node_t op_node = nullptr;
				if (scanner.is('*'))
				{
					scanner.next_symbol('*');
					op_node = new StNodeOperator<double>(StNodeOperator<double>::Operator::MUL);
				}
				else if (scanner.is('/'))
				{
					scanner.next_symbol('/');
					op_node = new StNodeOperator<double>(StNodeOperator<double>::Operator::DIV);
				}
				ref->set_right(op_node);

				ref = op_node;
				ref->set_left(right);

				right = parse_Factor();
			}

			if (ref != nullptr)
				ref->set_right(right);
			else
				root = left;

			return root;
		}

		// Optional sign and UFactor
		node_t parse_Factor() {
			if (!is_tb_Factor())
			{
				throw ParserException("Error parsing 'Factor'.");
			}

			// optional sign
			double const sign{ is_tb_AddOp() ? parse_AddOp() : 1.0 };
			
			// Multiplication (to account for the sign) has to be done through operator nodes.
			node_t root = new StNodeOperator<double>(StNodeOperator<double>::Operator::MUL);
			root->set_left(new StNodeValue<double>(sign));
			// Then delegate to UFactor
			root->set_right(parse_UFactor());

			return root;
		}

		// Monom or PExpression
		node_t parse_UFactor()
		{
			if (!is_tb_UFactor())
			{
				throw ParserException("Error parsing 'UFactor'.");
			}

			node_t root = nullptr;

			// UFactor can either be a Monom or PExpression. Delegate to the right parse function.
			if (is_tb_Monom())
			{
				root = parse_Monom();
			}
			else if (is_tb_PExpression())
			{
				root = parse_PExpression();
			}
			else
			{
				throw ParserException("Error parsing 'Factor'.");
			}

			return root;
		}

		// Number/variable followed by an optional exponent
		node_t parse_Monom() {
			if (!is_tb_Monom())
			{
				throw ParserException("Error parsing 'Monom'.");
			}

			// A Monom is a WMonom (delegation) followed by an optional exponent.
			// --> Operator node required
			node_t root = new StNodeOperator<double>(StNodeOperator<double>::Operator::EXP);
			root->set_left(parse_WMonom());

			// e^1 = e. If there is no exponent, we jut set it to one. Otherwise it becomes the stated value.
			node_t exp_node = { is_tb_Exponent() ? parse_Exponent() : new StNodeValue<double>(1) };

			root->set_right(exp_node);

			return root;
		}

		// exponent sign followed by sign and number
		node_t parse_Exponent() {
			if (!is_tb_Exponent())
			{
				throw ParserException("Error parsing 'Exponent'.");
			}

			node_t root = new StNodeOperator<double>(StNodeOperator<double>::Operator::MUL);
			double exp = 1.0f;

			// An exponent expression starts with '^'. Skip the character and parse the exponent and optional sign.
			scanner.next_symbol('^');
			double const sign{ is_tb_AddOp() ? parse_AddOp() : 1.0 };

			// Again, to apply the sign, add both values to the Operator Node.
			root->set_left(new StNodeValue<double>(sign));
			root->set_right(parse_WMonom());

			return root;
		}

		// Number or Variable
		node_t parse_WMonom() {
			if (!is_tb_WMonom())
			{
				throw ParserException("Error parsing 'WMonom'.");
			}

			node_t root = nullptr;

			// WMonom is either an identifer (variable) or an unsigned number. Parse them accordingly and skip to the next symbol.
			if (is_tb_Identifier())
			{
				root = new StNodeIdent<double>(scanner.current_symbol().get_identifier()); scanner.next_symbol();
			}
			else if(is_tb_Unsigned())
			{
				root = new StNodeValue<double>(scanner.get_number()); scanner.next_symbol();
			}

			return root;
		}

		double parse_AddOp()
		{
			// parse AddOp remains unchanged and returns -1.0 for - and +1.0 for +
			if (!is_tb_AddOp())
			{
				throw ParserException("Error parsing 'AddOp'.");
			}

			double sign{ 0.0 };
			if (scanner.is('+'))
			{
				sign = 1;
				scanner.next_symbol();
			}
			else if (scanner.is('-'))
			{
				sign = -1;
				scanner.next_symbol();
			}
			else
			{
				throw ParserException("Error parsing 'AddOp'.");
			}

			return sign;
		}

		// expression in parentheses
		node_t parse_PExpression()
		{
			if (!is_tb_PExpression())
			{
				throw ParserException("Error parsing 'PExpression'.");
			}

			// PExpression also remains unchanged and delegates to the altered parse_Expression()
			scanner.next_symbol('(');
			node_t root(parse_Expression());
			scanner.next_symbol(')');

			return root;
		}
	};

}

#endif