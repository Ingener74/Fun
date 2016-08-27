#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL int FunLexer::yylex()

#include <FunParser.hpp>

class FunLexer : public yyFlexLexer {
public:
    FunLexer(const std::string& filename, std::istream*);
    virtual ~FunLexer();

    int yylex(fun::FunParser::semantic_type* yylval, fun::FunParser::location_type* yylloc);

private:
    int yylex();
    fun::FunParser::semantic_type* yylval = nullptr;
    fun::FunParser::location_type* yylloc = nullptr;
    std::string _filename;
    int line = 1;
    int column = 0;
};
