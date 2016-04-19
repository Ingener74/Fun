#include "MyLexer.h"

MyLexer::MyLexer(std::istream* in)
    : yyFlexLexer(in){
}

MyLexer::~MyLexer(){
}

int MyLexer::yylex(myparser::parser::semantic_type* yylval){
    this->yylval = yylval;
    return yylex();
}
