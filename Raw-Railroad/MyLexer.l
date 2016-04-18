
%top{
    // Top block
}

%{

#include <iostream>

using namespace std;

#include <MyParser.hpp>

%}

%option c++
%option noyywrap

/* %option yyclass="MyFlexLexer" */

DIGIT    [0-9]+
ID       [a-zA-Z]+

%%

%{
int nnn1 = 0;
%}

DIGIT {
    cout << "Number " << yytext << endl; 
    yylval.num = atoi(yytext); 
    return NUM; 
}

ID {
    cout << "Identifier " << yytext << endl;
    yylval.str = new string(yytext);
    return ID;
}

. return 0;

%%

int yylex(){
    return NUM;
}


