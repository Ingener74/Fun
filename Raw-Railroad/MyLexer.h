#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL int MyLexer::yylex()

#include <MyParser.hpp>

class MyLexer : public yyFlexLexer {
public:
    MyLexer(std::istream*);
    virtual ~MyLexer();

    int yylex(myparser::parser::semantic_type* yylval);

private:
    int yylex();
    myparser::parser::semantic_type* yylval;
};
