%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"
%defines

// %verbose
%define parser_class_name {Parser}
%define api.namespace {bison}

%code{
static int yylex(bison::Parser::semantic_type *yylval,
                 Lexer &lexer);
}

%{

#include <iostream>

using namespace std;

%}

%token ID NUMBER
%token ADD SUB MUL DIV ASSIGN ABS
%token EOL EOE

%%

calclist:
    | calclist exp EOL { cout << "| calclist exp EOL" << endl; }
    ;

exp: factor
    | exp ADD factor { $$ = $1 + $3; }
    | exp SUB factor { $$ = $1 - $3; }
    ;

factor: term
    | factor MUL term { $$ = $1 * $3; }
    | factor DIV term { $$ = $1 / $3; }
    ;

term: NUMBER
    | ABS term { $$ = $2 >= 0 : $2 : -$2; }
    ;

%%

/*
int main(int , char* []){
}
*/