#ifndef arithmetic_parser_h
#define arithmetic_parser_h

#include <iostream>
#include <string>
#include <exception>
#include "pfc_scanner.h"

class ParserException final : public std::runtime_error {
public:
    explicit ParserException (std::string const & message) : std::runtime_error {message} { }
};

class ArithmeticParser {
public:
    double parse (std::istream & in);
    double parse (std::string const & filename);
    
private:
    
    bool is_tb_Expression() const;
    bool is_tb_Term() const;
    bool is_tb_Factor() const;
    bool is_tb_AddOp() const;
    bool is_tb_MultOp() const;
    bool is_tb_PExpression() const;
    bool is_tb_Unsigned() const;
    
    double parse_Expression();
    double parse_Term();
    double parse_Factor();
    double parse_AddOp();
    double parse_PExpression();
    // Already exists in pfc_scanner
    //double parse_Unsigned();

    pfc::scanner m_scanner;
};

#endif /* arithmetic_parser_h */
