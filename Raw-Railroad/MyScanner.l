
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

DIGIT    [0-9]+
ID       [a-zA-Z]+

%%

%{
int nnn1 = 0;
%}

{DIGIT} {
    cout << "Number " << yytext << endl; 
    yylval->num = atoi(yytext); 
    return myparser::parser::token::NUM; 
}

{ID} {
    cout << "Identifier " << yytext << endl;
    yylval->str = new string(yytext);
    return myparser::parser::token::ID;
}

"=" {
    cout << "Assign " << endl;
    return myparser::parser::token::ASSIGN;
}

"\n" {
    cout << "End of line" << endl;
    return myparser::parser::token::EOL;
}

. { cerr << "Invalid symbol " << yytext << endl; }

%%

