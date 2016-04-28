
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

"import" return myparser::parser::token::IMPORT;
"print" return myparser::parser::token::PRINT;
"fun" return myparser::parser::token::FUN;
"end" return myparser::parser::token::END;

"(" return myparser::parser::token::LPAREN;
")" return myparser::parser::token::RPAREN;
"," return myparser::parser::token::COMMA;

{DIGIT} {
    yylval->num = atoi(yytext); 
    return myparser::parser::token::NUM; 
}

{ID} {
    yylval->str = new string(yytext);
    return myparser::parser::token::ID;
}

"="  return myparser::parser::token::ASSIGN;

[ \t\n] ;

. { cerr << "Invalid symbol " << yytext << endl; }

%%

