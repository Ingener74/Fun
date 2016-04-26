%require "3.0.4"
%skeleton "lalr1.cc"

/* %defines */

%debug
%define api.namespace {myparser}

%code requires{
class MyLexer;

//class MyAst;

#include "MyAst.h"

#include "Expr.h"
#include "AssignExpr.h"
#include "IdExpr.h"
#include "NumExpr.h"

#include "FuncType.h"
#include "DefineType.h"
#include "ArgType.h"
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
    Import* import;
}

%destructor { delete $$; /* string destructor */ } <str> <expr_type> <func_type> <arg_type> <import> // <define_type>  

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

%type <expr_type> expr
%type <func_type> func
// %type <define_type> define
%type <arg_type> arg
%type <import> import_type

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
    : %empty
    | root imports
    | root defines
    | root line
    ;

imports
    : IMPORT ID EOL {  }
    | imports
    ;

defines
    : func defines  { myAst->functionDefinition($1); }
    | expr defines { myAst->functionDefinition($1); }
    ;

func
    : FUN ID "(" arg ")" expr END { $$ = new FuncType($2, $4, $6); }
    ;

arg
    : ID "," arg   { $$ = new IdExpr($1); }
    ;

line
    : EOL
    | expr EOL { /* cout << $1->toString() << endl; */ }
    ;

expr
    : ID "=" NUM { $$ = new AssignExpr(*$1, $3); myAst->addVariable(*$1, $3); }
    | PRINT ID { myAst->printVariable(*$2); }
    ;

%%

#include <MyLexer.h>

int yylex(myparser::parser::semantic_type* yylval, MyLexer& myLexer){
    return myLexer.yylex(yylval);
}

void myparser::parser::error(const std::string& message){
    cerr << "error: " << message << endl;
}

