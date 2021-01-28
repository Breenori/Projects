#include "arithmetic_parser.h"
#include<istream>
#include<string>
#include "divide_by_zero_exception.h"
using std::istream;
using std::string;
using std::istringstream;

double ArithmeticParser::parse(istream& in)
{
	m_scanner.set_istream(in);
	double const result = parse_PrefixExpression();
	m_scanner.set_istream();
	return result;
}

// Terminal beginnings
double ArithmeticParser::parse(string const& filename)
{
	istringstream in(filename);
	return parse(in);
}
/*bool ArithmeticParser::is_tb_Term() const
{
	return is_tb_Factor();
}*/
bool ArithmeticParser::is_tb_Factor() const
{
	return is_tb_AddOp() || is_tb_Unsigned();// || is_tb_PExpression();
}
bool ArithmeticParser::is_tb_AddOp() const
{
	return m_scanner.is('+') || m_scanner.is('-');
}
bool ArithmeticParser::is_tb_MultOp() const
{
	return m_scanner.is('*') || m_scanner.is('/');
}
bool ArithmeticParser::is_tb_Unsigned() const
{
	return m_scanner.is_number();
}

// Parsers
double ArithmeticParser::parse_PrefixExpression()
{
	if (!(is_tb_AddOp() || is_tb_MultOp() || is_tb_Unsigned()))
	{
		throw ParserException("Error parsing 'Expression'.");
	}

	double value(0);
	double left(0);
	double right(0);
	
	if (is_tb_AddOp())
	{
		double const sign{ parse_AddOp() };
		left = parse_PrefixExpression();
		right = parse_PrefixExpression();
		
		if(sign == 1)
		{
			value = left + right;
		}
		else
		{
			value = left - right;
		}
	}
	else if (is_tb_MultOp())
	{		
		if(m_scanner.is('/'))
		{
			m_scanner.next_symbol();
			left = parse_PrefixExpression();
			right = parse_PrefixExpression();
			value = left / right;
		}
		else
		{
			m_scanner.next_symbol();
			left = parse_PrefixExpression();
			right = parse_PrefixExpression();
			value = left * right;
		}
	}
	else
	{
		value = m_scanner.get_number(); m_scanner.next_symbol();
	}
	
	
	return value;
}
/*double ArithmeticParser::parse_Expression()
{
	if (!is_tb_Expression())
	{
		throw ParserException("Error parsing 'Expression'.");
	}

	double value(parse_Term());
	while (is_tb_AddOp())
	{
		double const sign{ parse_AddOp() };
		value += sign * parse_Term();
	}

	return value;
}
double ArithmeticParser::parse_Term()
{
	if (!is_tb_Term())
	{
		throw ParserException("Error parsing 'Term'.");
	}

	double value(parse_Factor());

	while (is_tb_MultOp())
	{
		if (m_scanner.is('*'))
		{
			// character as parameter: checks if '*' is current symbol before going to next symbol. Otherwise throws exception.
			m_scanner.next_symbol('*');
			value *= parse_Factor();
		}
		else if (m_scanner.is('/'))
		{
			m_scanner.next_symbol('/');

			double divisor = parse_Factor();
			if(divisor == 0)
			{
				throw divide_by_zero_exception();
			}
			
			value /= divisor;
		}
		else
		{
			throw ParserException("Error parsing 'Term'.");
		}
	}

	return value;
}
double ArithmeticParser::parse_Factor() {
	if (!is_tb_Factor())
	{
		throw ParserException("Error parsing 'Factor'.");
	}

	double const sign{ is_tb_AddOp() ? parse_AddOp() : 1.0 };
	double value(0.0);

	if (is_tb_Unsigned())
	{
		value = m_scanner.get_number(); m_scanner.next_symbol();
	}
	else if (is_tb_PExpression())
	{
		value = parse_PExpression();
	}
	else
	{
		throw ParserException("Error parsing 'Factor'.");
	}

	return sign * value;
}*/
double ArithmeticParser::parse_AddOp()
{
	if (!is_tb_AddOp())
	{
		throw ParserException("Error parsing 'AddOp'.");
	}

	double sign{ 0.0 };
	if (m_scanner.is('+'))
	{
		sign = 1;
		m_scanner.next_symbol();
	}
	else if (m_scanner.is('-'))
	{
		sign = -1;
		m_scanner.next_symbol();
	}
	else
	{
		throw ParserException("Error parsing 'AddOp'.");
	}

	return sign;
}
/*double ArithmeticParser::parse_PExpression()
{
	if (!is_tb_PExpression())
	{
		throw ParserException("Error parsing 'PExpression'.");
	}

	m_scanner.next_symbol('(');
	double const value(parse_Expression());
	m_scanner.next_symbol(')');

	return value;
}*/
// double ArithmeticParser::parse_Unsigned();