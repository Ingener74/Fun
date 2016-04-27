%require "3.0.4"
%skeleton "lalr1.cc"

%debug
%define api.namespace {myparser}

%code requires{
class MyLexer;

#include "MyAst.h"

#include "Expr.h"
#include "AssignExpr.h"
#include "IdExpr.h"
#include "NumExpr.h"

#include "FuncType.h"
#include "DefineType.h"
#include "ArgType.h"
#include "Import.h"
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
    FuncType* func_type;
    DefineType* define_type;
    ArgType* arg_type;
    Import* import_type;
}

%destructor { delete $$; } <str> <import_type> // <define_type> <expr_type> <func_type> <arg_type>

%code{
int yylex(myparser::parser::semantic_type* , MyLexer&);
}

%token <num> NUM
%token <str> ID
%token EOL
%token <chr> ASSIGN "="

%token LPAREN "("
%token RPAREN ")"
%token COMMA ","

%token IMPORT
%token PRINT
%token FUN
%token END

// %type <expr_type> expr
// %type <func_type> func
// %type <define_type> define
// %type <arg_type> arg
%type <import_type> import

%param{ 
    MyLexer& myLexer
};

%parse-param { MyAst* myAst };

%initial-action
{
    // Initial code
};

%%

%start root;

root
    : import

import
    : "import" ID EOL { $$ = new Import(*$2); cout << $2 << endl; }
    ;

%%

#include <MyLexer.h>

int yylex(myparser::parser::semantic_type* yylval, MyLexer& myLexer){
    return myLexer.yylex(yylval);
}

void myparser::parser::error(const std::string& message){
    cerr << "error: " << message << endl;
}

