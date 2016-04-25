
%top{
    // Top block
}

%{

#include <iostream>

using namespace std;

#include <MyParser.hpp>
#include <MyLexer.h>

%}

%option c++
%option noyywrap

%option yyclass="MyLexer"

DIGIT    [0-9]*
ID       [a-zA-Z_][a-zA-Z_0-9]*

%%

%{
int nnn1 = 0;
%}

{DIGIT} {
    yylval->num = atoi(yytext); 
    return myparser::parser::token::NUM; 
}

{ID} {
    yylval->str = new string(yytext);
    return myparser::parser::token::ID;
}

"="  return myparser::parser::token::ASSIGN;
"\n" return myparser::parser::token::EOL;

[ \t] ;

. { cerr << "Invalid symbol " << yytext << endl; }

%%

