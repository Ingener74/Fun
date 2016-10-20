#include <iostream>
#include "Lexer.h"

using namespace std;

Lexer::Lexer(const std::string& filename, std::istream &in, bool debug) :
        yyFlexLexer(in, cout), _filename(filename), line(1), column(0), _debug(debug) {
}

//Lexer::Lexer(const std::string& source, bool debug) :
//        yyFlexLexer(&sourceCode), sourceCode(source), _filename(), line(1), column(0), _debug(debug) {
//}

Lexer::~Lexer() {
}

int Lexer::yylex(fun::Parser::semantic_type *yylval, fun::Parser::location_type *yylloc) {
    this->yylval = yylval;
    this->yylloc = yylloc;
    if (!_filename.empty())
        this->yylloc->initialize(&_filename);
    return yylex();
}
