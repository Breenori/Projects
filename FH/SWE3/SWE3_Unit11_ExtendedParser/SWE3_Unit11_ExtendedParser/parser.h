#ifndef PARSER_H
#define PARSER_H
#include "pfc_scanner.h"
#include "syntax_tree.h"
#include "name_list.h"

namespace xpr
{
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
	};

	class ParseSyntaxTree : public Parser
	{
	public:
		typedef StNode<double>* node_t;
		typedef NameList<SyntaxTree<double>*>* name_t;
		ParseSyntaxTree(std::istream& in)
		{
			scanner.register_keyword("print");
			scanner.register_keyword("set");
			scanner.set_istream(in);
			name_list = new NameListMap<SyntaxTree<double>*>();
		}

		virtual ~ParseSyntaxTree()
		{
			delete name_list;
		}

		void parse() override
		{
			parse_Programm();
		}

	private:
		name_t name_list;


		bool is_tb_Programm()
		{
			return is_tb_Ausgaben() || is_tb_Zuweisungen();
		}

		bool is_tb_Ausgaben()
		{
			return is_tb_Ausgabe();
		}
		bool is_tb_Ausgabe()
		{
			return scanner.is_keyword("print");
		}

		bool is_tb_Zuweisungen()
		{
			return is_tb_Zuweisung();
		}
		bool is_tb_Zuweisung()
		{
			return scanner.is_keyword("set");
		}

		void parse_Programm()
		{
			if (!is_tb_Programm())
			{
				throw ParseException("Parse exception in Rule 'Program'.");
			}

			while (is_tb_Programm())
			{
				if (is_tb_Ausgaben())
				{
					parse_Ausgaben();
				}
				else if (is_tb_Zuweisungen())
				{
					parse_Zuweisungen();
				}
			}
		}
			
		void parse_Ausgaben()
		{
			if (!is_tb_Ausgaben())
			{
				throw ParseException("Parse exception in rule 'Ausgaben'.");
			}

			parse_Ausgabe();
			while (is_tb_Ausgabe())
			{
				parse_Ausgabe();
			}
		}

		void parse_Zuweisungen()
		{
			if (!is_tb_Zuweisungen())
			{
				throw ParseException("Parse exception in rule 'Zuweisungen'.");
			}

			parse_Zuweisung();
			while (is_tb_Zuweisung())
			{
				parse_Zuweisung();
			}
		}

		void parse_Zuweisung()
		{
			if (!is_tb_Zuweisung())
			{
				throw ParseException("Parse exception in rule 'Zuweisung'.");
			}

			scanner.next_symbol("set");
			scanner.next_symbol("(");
			std::string identifier = scanner.get_identifier();
			scanner.next_symbol(',');

			node_t root = parse_Ausdruck();
			scanner.next_symbol(")");
			scanner.next_symbol(";");

			name_list->register_variable(identifier, new SyntaxTree<double>(root));
		}

		void parse_Ausgabe()
		{
			if (!is_tb_Ausgabe())
			{
				throw ParseException("Parse exception in rule 'Ausgabe'.");
			}

			scanner.next_symbol("print");
			scanner.next_symbol("(");
			node_t root = parse_Ausdruck();
			scanner.next_symbol(")");
			scanner.next_symbol(";");

			SyntaxTree<double>* st = new SyntaxTree<double>(root);
			std::cout << st->evaluate(name_list) << std::endl;
			// std::cout << st;
			delete st;
		}

		node_t parse_Ausdruck()
		{

		}
	};

}

#endif