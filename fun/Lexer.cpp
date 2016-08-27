#include "Lexer.h"

Lexer::Lexer(const std::string& filename, std::istream *in)
        : yyFlexLexer(in), _filename(filename), line(0), column(0) {
}

Lexer::~Lexer() {
}

int Lexer::yylex(fun::Parser::semantic_type *yylval, fun::Parser::location_type *yylloc) {
    this->yylval = yylval;
    this->yylloc = yylloc;
    if(!_filename.empty())
        this->yylloc->initialize(&_filename);
    return yylex();
}
