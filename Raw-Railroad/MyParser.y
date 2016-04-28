%require "3.0.4"
%skeleton "lalr1.cc"

// %debug
%define parse.trace

%define api.namespace {myparser}

%code requires{
class MyLexer;

#include "MyAst.h"

#include "Expr.h"
#include "AssignExpr.h"
#include "IdExpr.h"
#include "NumExpr.h"

#include "Function.h"
#include "DefineType.h"
#include "Args.h"
#include "Import.h"
#include "Print.h"
#include "Plus.h"
#include "Minus.h"
#include "Mul.h"
#include "Div.h"
#include "FunctionStatements.h"
}

%{

#include <iostream>

using namespace std;

void yyerror(const char* );

%}

%union{
    int num;
    std::string* str;
    char chr;
    Expr* expr_type;
    Function* func_type;
    DefineType* define_type;
    Args* arg_type;
    Import* import_type;
    Print* print_type;
    FunctionStatements* func_sttmnt_type;
}

%destructor { delete $$; } <str> <import_type> <expr_type> <print_type> <func_type> <arg_type> <func_sttmnt_type>// <define_type>  

%code{
int yylex(myparser::parser::semantic_type* , MyLexer&);
}

%token <num> NUM
%token <str> ID
%token EOL

%token ASSIGN "="
%token <chr> PLUS "+"
%token <chr> MINUS "-"
%token <chr> MUL "*"
%token <chr> DIV "/"

%token LPAREN "("
%token RPAREN ")"
%token COMMA ","

%token IMPORT "import"
%token PRINT "print"
%token FUN "fun"
%token END "end"

%type <expr_type> expr
%type <func_type> func
// %type <define_type> define
%type <arg_type> func_arg
%type <import_type> import
%type <print_type> print

%type <func_sttmnt_type> func_sttmts

%param{ 
    MyLexer& myLexer
};

%parse-param { MyAst* myAst };

%initial-action
{
    // Initial code
};

%left "="
%left "+" "-"
%left "*" "/"

%%

%start root;

root
    : %empty 
    | root import { myAst->importLibrary($2); }
    | root expr   { $2->visit(myAst); }
    | root print  { myAst->printId($2); }
    | root func   { myAst->functionDefinition($2); }
    ;

import
    : "import" ID { $$ = new Import(*$2); }
    ;
    
func
    : "fun" ID "(" func_arg ")" func_sttmts "end" { /* cout << "func def " << endl; */ $$ = new Function(*$2, $4, $6); }
    ;

func_arg
    : ID              { /* cout << "arg 2 def " << endl; */ $$ = new Args(*$1); }
    | func_arg "," ID { /* cout << "arg 1 def " << endl; */ $1->addArg(*$3); }
    ;

func_sttmts
    : %empty           { /* cout << "expression" << endl; */   $$ = new FunctionStatements(); }
    | expr             { /* cout << "expression 1" << endl; */ $$ = new FunctionStatements($1); }
    | func_sttmts expr { /* cout << "expression 2" << endl; */ $1->addExpression($2); }
    ;

expr
    : ID "=" expr { $$ = new AssignExpr(*$1, $3); }
    | expr "+" expr { $$ = new Plus($1, $3); }
    | expr "-" expr { $$ = new Minus($1, $3); }
    | expr "*" expr { $$ = new Mul($1, $3); }
    | expr "/" expr { $$ = new Div($1, $3); }
    | NUM { $$ = new NumExpr($1); }
    ;

print
    : "print" ID { $$ = new Print(*$2); }
    ;

%%

#include <MyLexer.h>

int yylex(myparser::parser::semantic_type* yylval, MyLexer& myLexer) {
    return myLexer.yylex(yylval);
}

void myparser::parser::error(const std::string& message) {
    cerr << "error: " << message << endl;
}

