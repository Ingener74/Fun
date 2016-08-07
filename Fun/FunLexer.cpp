#include "FunLexer.h"

FunLexer::FunLexer(const std::string& filename, std::istream *in)
        : yyFlexLexer(in), _filename(filename), line(0), column(0) {
}

FunLexer::~FunLexer() {
}

int FunLexer::yylex(fun::FunParser::semantic_type *yylval, fun::FunParser::location_type *yylloc) {
    this->yylval = yylval;
    this->yylloc = yylloc;
    if(!_filename.empty())
        this->yylloc->initialize(&_filename);
    return yylex();
}
