#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL int Lexer::yylex()

#include <Parser.hpp>

class Lexer: public yyFlexLexer {
public:
    Lexer(const std::string& filename, std::istream*, bool debug = false);
    Lexer(const std::string& sourceCode, bool debug = false);
    virtual ~Lexer();

    int yylex(fun::Parser::semantic_type* yylval, fun::Parser::location_type* yylloc);

private:
    int yylex();
    fun::Parser::semantic_type* yylval = nullptr;
    fun::Parser::location_type* yylloc = nullptr;
    std::string _filename;
    int line = 1;
    int column = 0;
    bool _debug = false;
    std::stringstream sourceCode;
};
