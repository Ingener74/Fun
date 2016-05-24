#include "FunLexer.h"

FunLexer::FunLexer(std::istream* in)
    : yyFlexLexer(in){
}

FunLexer::~FunLexer(){
}

int FunLexer::yylex(fun::FunParser::semantic_type* yylval){
    this->yylval = yylval;
    return yylex();
}
