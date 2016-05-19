#include "FunLexer.h"

FunLexer::FunLexer(std::istream* in)
    : yyFlexLexer(in){
}

FunLexer::~FunLexer(){
}

int FunLexer::yylex(myparser::parser::semantic_type* yylval){
    this->yylval = yylval;
    return yylex();
}
