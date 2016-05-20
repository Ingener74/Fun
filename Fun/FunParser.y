%require "3.0.4"
%skeleton "lalr1.cc"

%debug

%define api.namespace {myparser}

%code requires{
class FunLexer;

#include "FunAst.h"

#include "Scope.h"
#include "Function.h"
#include "ArgumentList.h"
#include "Import.h"
#include "Print.h"
#include "If.h"

#include "Expression.h"
#include "ExpressionList.h"
#include "Assign.h"
#include "Id.h"
#include "Integer.h"
#include "BinaryOp.h"
#include "Call.h"

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
    
    fun::Scope* scope_type;
    fun::ExpressionList* expr_list_type;
    fun::Function* func_type;
    fun::ArgumentList* arg_type;
    fun::Import* import_type;
    fun::Print* print_type;
    fun::If* if_type;
    fun::Id* id_type;
    
    fun::Expression* expr_type;
}

%destructor { delete $$; } <str> <scope_type> <import_type> <expr_type> <print_type> <func_type> <arg_type> <if_type> <expr_list_type> <id_type>

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
%token <chr> MORE ">"

%token COLON  ":"
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

%type <id_type> id
%type <expr_type> expr
%type <func_type> func
%type <arg_type> func_arg
%type <import_type> import
%type <print_type> print

%type <scope_type> scope
%type <if_type> if

%type <expr_list_type> expr_list

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
    : %empty       { $$ = new fun::Scope(); ast->setRoot($$); }
    | scope import { $1->addStatement($2); }
    | scope expr   { $1->addStatement($2); }
    | scope print  { $1->addStatement($2); }
    | scope func   { $1->addStatement($2); }
    | scope if     { $1->addStatement($2); }
    ;

id
    : ID { $$ = new fun::Id(*$1); }
    ;

import
    : "import" id { $$ = new fun::Import($2); }
    ;

func
    : "fun" id "(" func_arg ")" scope "end" { $$ = new fun::Function($2, $4, $6); }
    ;

func_arg
    : %empty          { $$ = new fun::ArgumentList(); }
    | id              { $$ = new fun::ArgumentList($1); }
    | func_arg "," id { $1->addArg($3); }
    ;

expr
    : id "=" expr { $$ = new fun::Assign($1, $3); }
    | expr "+" expr { $$ = new fun::BinaryOp(fun::BinaryOp::PLUS, $1, $3); }
    | expr "-" expr { $$ = new fun::BinaryOp(fun::BinaryOp::MINUS, $1, $3); }
    | expr "*" expr { $$ = new fun::BinaryOp(fun::BinaryOp::MULTIPLY, $1, $3); }
    | expr "/" expr { $$ = new fun::BinaryOp(fun::BinaryOp::DIVIDE, $1, $3); }
    | expr ">" expr { $$ = new fun::BinaryOp(fun::BinaryOp::MORE, $1, $3); }
    | NUM { $$ = new fun::Integer($1); }
    | id 
    | id "(" expr_list ")" { $$ = new fun::Call($1, $3); }
    ;

expr_list
    : %empty             { $$ = new fun::ExpressionList(); }
    | expr               { $$ = new fun::ExpressionList($1); }
    | expr "," expr_list { $3->addExpression($1); }
    ;

print
    : "print" expr { $$ = new fun::Print($2); }
    ;

if
    : "if" expr ":" scope "end"               { $$ = new fun::If($2, $4); }
    | "if" expr ":" scope "else" scope "end"  { $$ = new fun::If($2, $4, $6); }
    ;

%%

#include <FunLexer.h>

int yylex(myparser::parser::semantic_type* yylval, FunLexer& myLexer) {
    return myLexer.yylex(yylval);
}

void myparser::parser::error(const std::string& message) {
    cerr << "error: " << message << endl;
}

