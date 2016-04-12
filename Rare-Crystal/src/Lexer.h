#pragma once

#if !defined(yyFlexLexerOnce)
    #include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL int Lexer::yylex();

#include "BisonParser.hh"

class Lexer : public yyFlexLexer {
public:
    Lexer(std::istream *in);
    virtual ~Lexer();

    int yylex(bison::Parser::semantic_type *l_val);

private:
    int yylex();
    bison::Parser::semantic_type *yylval;
};
