#include "Lexer.h"


Lexer::Lexer(std::istream *in)
        : yyFlexLexer(in)
        , yylval(nullptr) {
}

Lexer::~Lexer() {
}

int Lexer::yylex(bison::Parser::semantic_type *l_val) {
    yylval = l_val;
    return yylex();
}




