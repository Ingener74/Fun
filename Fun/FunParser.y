%require "3.0.4"
%skeleton "lalr1.cc"

%debug

%define api.namespace {myparser}

%code requires{
class FunLexer;

#include "FunAst.h"

#include "Scope.h"

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
    fun::Expr* expr_type;
    fun::Function* func_type;
    DefineType* define_type;
    fun::Args* arg_type;
    fun::Import* import_type;
    fun::Print* print_type;
    fun::FunctionStatements* func_sttmnt_type;
    
    fun::Scope* scope_type;
}

%destructor { delete $$; } <str> <scope_type> <import_type> <expr_type> <print_type> <func_type> <arg_type> <func_sttmnt_type>// <define_type>  

%code{
int yylex(myparser::parser::semantic_type* , FunLexer&);
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

%token IF "if"
%token ELSE "else"
%token FOR "for"
%token IN "in"
%token WHILE "while"
%token DO "do"
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

%type <scope_type> scope

%param{ 
    FunLexer& myLexer
};

%parse-param { fun::FunAst* ast };

%initial-action
{
    // Initial code
};

%left "="
%left "+" "-"
%left "*" "/"

%%

%start scope;

scope
    : %empty       { $$ = new fun::Scope(); ast->pushScope($$); }
    | scope import { $1->addStatement($2); }
    | scope expr   { $1->addStatement($2); }
    | scope print  { $1->addStatement($2); }
    | scope func   { $1->addStatement($2); }
    ;

import
    : "import" ID { $$ = new fun::Import(*$2); }
    ;
    
func
    : "fun" ID "(" func_arg ")" func_sttmts "end" { $$ = new fun::Function(*$2, $4, $6); }
    ;

func_arg
    : ID              { $$ = new fun::Args(*$1); }
    | func_arg "," ID { $1->addArg(*$3); }
    ;

func_sttmts
    : %empty           { $$ = new fun::FunctionStatements(); }
    | expr             { $$ = new fun::FunctionStatements($1); }
    | func_sttmts expr { $1->addExpression($2); }
    ;

expr
    : ID "=" expr { $$ = new fun::AssignExpr(*$1, $3); }
    | expr "+" expr { $$ = new fun::Plus($1, $3); }
    | expr "-" expr { $$ = new fun::Minus($1, $3); }
    | expr "*" expr { $$ = new fun::Mul($1, $3); }
    | expr "/" expr { $$ = new fun::Div($1, $3); }
    | NUM { $$ = new fun::NumExpr($1); }
    ;

print
    : "print" ID { $$ = new fun::Print(*$2); }
    ;

%%

#include <FunLexer.h>

int yylex(myparser::parser::semantic_type* yylval, FunLexer& myLexer) {
    return myLexer.yylex(yylval);
}

void myparser::parser::error(const std::string& message) {
    cerr << "error: " << message << endl;
}

