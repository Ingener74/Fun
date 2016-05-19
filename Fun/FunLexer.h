#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL int FunLexer::yylex()

#include <FunParser.hpp>

class FunLexer : public yyFlexLexer {
public:
    FunLexer(std::istream*);
    virtual ~FunLexer();

    int yylex(myparser::parser::semantic_type* yylval);

private:
    int yylex();
    myparser::parser::semantic_type* yylval = nullptr;
};
