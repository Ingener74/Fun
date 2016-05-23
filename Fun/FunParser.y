%require "3.0.4"
%skeleton "lalr1.cc"

%debug

%define api.namespace {myparser}

%code requires{

class FunLexer;

#include "FunAst.h"

#include "Statement.h"
#include "Scope.h"
#include "Function.h"
#include "ArgumentList.h"
#include "Import.h"
#include "Print.h"
#include "If.h"
#include "While.h"

#include "Expression.h"
#include "ExpressionList.h"
#include "Assign.h"
#include "Id.h"
#include "Integer.h"
#include "Real.h"
#include "BinaryOp.h"
#include "Call.h"

}

%{
#include <iostream>
using namespace std;
void yyerror(const char* );
%}

%union{
    long long int         integer;
    double                real;
    std::string*          str;
    
    fun::Scope*           scope_type;
    fun::Statement*       statement_type;
    fun::ExpressionList*  expr_list_type;
    fun::Function*        func_type;
    fun::ArgumentList*    arg_type;
    fun::Import*          import_type;
    fun::Print*           print_type;
    fun::If*              if_type;
    fun::While*           while_type;
    fun::Id*              id_type;    
    fun::Expression*      expr_type;
}

%destructor { delete $$; } <str> <scope_type> <import_type> <expr_type> <print_type> <func_type> <arg_type> <if_type> <expr_list_type> <id_type> <statement_type> <while_type>

%code{
int yylex(myparser::parser::semantic_type* , FunLexer&);
}

%token <integer>          INTEGER
%token <real>             REAL
%token <str>              ID
%token EOL

%token ASSIGN             "="

%token ADD                "+"
%token ADD_ASSIGN         "+="

%token SUB                "-"
%token SUB_ASSIGN         "-="

%token MUL                "*"
%token MUL_ASSIGN         "*="

%token DIV                "/"
%token DIV_ASSIGN         "/="

%token MOD                "%"
%token MOD_ASSIGN         "%="

%token MORE               ">"
%token MORE_EQUAL         ">="

%token LESS               "<"
%token LESS_EQUAL         "<="

%token COLON              ":"
%token LPAREN             "("
%token RPAREN             ")"
%token COMMA              ","

%token IMPORT             "import"
%token IF                 "if"
%token ELSE               "else"
%token FOR                "for"
%token IN                 "in"
%token WHILE              "while"
%token DO                 "do"
%token FUN                "fun"
%token PRINT              "print"
%token RETURN             "ret"
%token END                "end"

%type <scope_type>        scope
%type <statement_type>    statement
%type <id_type>           id
%type <expr_type>         expr
%type <func_type>         func
%type <arg_type>          func_arg
%type <import_type>       import
%type <print_type>        print
%type <if_type>           if
%type <while_type>        while
%type <expr_list_type>    expr_list

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
    : %empty          { $$ = new fun::Scope(); ast->setRoot($$); }
    | scope statement { $1->addStatement($2); }
    | scope expr      { $1->addStatement($2); }
    ;

statement
    : import
    | print 
    | func
    | if
    | while
    ;

id
    : ID { $$ = new fun::Id(*$1); }
    ;

import
    : "import" id             { $$ = new fun::Import($2); }
    ;

func
    : "fun" id "(" func_arg ")" scope "end" { $$ = new fun::Function($2, $4, $6); }
    ;

func_arg
    : %empty                 { $$ = new fun::ArgumentList();   }
    | id                     { $$ = new fun::ArgumentList($1); }
    | func_arg "," id        { $1->addArg($3);                 }
    ;

expr
    : id "=" expr            { $$ = new fun::Assign($1, $3); }
    | expr "+" expr          { $$ = new fun::BinaryOp(fun::BinaryOp::ADD, $1, $3); }
    | expr "+=" expr         { $$ = new fun::BinaryOp(fun::BinaryOp::ADD_ASSIGN, $1, $3); }
    | expr "-" expr          { $$ = new fun::BinaryOp(fun::BinaryOp::SUB, $1, $3); }
    | expr "-=" expr         { $$ = new fun::BinaryOp(fun::BinaryOp::SUB_ASSIGN, $1, $3); }
    | expr "*" expr          { $$ = new fun::BinaryOp(fun::BinaryOp::MUL, $1, $3); }
    | expr "*=" expr         { $$ = new fun::BinaryOp(fun::BinaryOp::MUL_ASSIGN, $1, $3); }
    | expr "/" expr          { $$ = new fun::BinaryOp(fun::BinaryOp::DIV, $1, $3); }
    | expr "/=" expr         { $$ = new fun::BinaryOp(fun::BinaryOp::DIV_ASSIGN, $1, $3); }
    | expr "%" expr          { $$ = new fun::BinaryOp(fun::BinaryOp::MOD, $1, $3); }
    | expr "%=" expr         { $$ = new fun::BinaryOp(fun::BinaryOp::MOD_ASSIGN, $1, $3); }
    | expr ">" expr          { $$ = new fun::BinaryOp(fun::BinaryOp::MORE, $1, $3); }
    | expr ">=" expr         { $$ = new fun::BinaryOp(fun::BinaryOp::MORE_EQUAL, $1, $3); }
    | expr "<" expr          { $$ = new fun::BinaryOp(fun::BinaryOp::LESS, $1, $3); }
    | expr "<=" expr         { $$ = new fun::BinaryOp(fun::BinaryOp::LESS_EQUAL, $1, $3); }
    | INTEGER                { $$ = new fun::Integer($1); }
    | REAL                   { $$ = new fun::Real($1); }
    | id 
    | id "(" expr_list ")"   { $$ = new fun::Call($1, $3); }
    ;

expr_list
    : %empty                 { $$ = new fun::ExpressionList(); }
    | expr                   { $$ = new fun::ExpressionList($1); }
    | expr "," expr_list     { $3->addExpression($1); }
    ;

print
    : "print" expr { $$ = new fun::Print($2); }
    ;

if
    : "if" expr ":" scope "end"               { $$ = new fun::If($2, $4); }
    | "if" expr ":" scope "else" scope "end"  { $$ = new fun::If($2, $4, $6); }
    ;

while
    : "while" expr ":" scope "end" { $$ = new fun::While($2, $4); }
    ;

%%

#include <FunLexer.h>

int yylex(myparser::parser::semantic_type* yylval, FunLexer& myLexer) {
    return myLexer.yylex(yylval);
}

void myparser::parser::error(const std::string& message) {
    cerr << "error: " << message << endl;
}

