%require "3.0.4"
%skeleton "lalr1.cc"

%debug

%define api.namespace {fun}
%define parser_class_name{FunParser}

%code requires{

class FunLexer;

#include "Nodes.h"

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
    
    Scope*                scope_type;
    Statement*            statement_type;
    Function*             func_type;
    Import*               import_type;
    Print*                print_type;
    If*                   if_type;
    While*                while_type;
    For*                  for_type;
    Return*               return_type;
    Id*                   id_type;    
    Expression*           expr_type;
}

// %destructor { delete $$; } <str> <scope_type> <import_type> <expr_type> <print_type> <func_type> <arg_type> <if_type> <expr_list_type> <id_type> <statement_type> <while_type>

%code{
int yylex(fun::FunParser::semantic_type* , FunLexer&);
}

%token <integer>          INTEGER
%token <real>             REAL
%token <str>              ID
%token <str>              STRING
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
%token SEMICOLON          ";"
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
%token TRUE               "true"
%token FALSE              "false"
%token CLASS              "class"
%token INIT               "init"

%type <scope_type>        scope
%type <statement_type>    statement
%type <statement_type>    statements
%type <id_type>           id
%type <id_type>           ids
%type <expr_type>         expr
%type <expr_type>         exprs
%type <func_type>         func
%type <import_type>       import
%type <print_type>        print
%type <if_type>           if
%type <while_type>        while
%type <for_type>          for
%type <return_type>       ret

%param { FunLexer& myLexer };
// %parse-param { fun::FunAst* ast };

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
    : %empty          { $$ = Node::make<Scope>(); if(!Node::root) Node::root = $$; }
    | scope statement { $1->m_statements.push_back($2); }
    | scope expr      { $1->m_statements.push_back($2); }
    ;

/*
statements
    : %empty
    | statement            { $$ = $1; if (!Node::root) Node::root = $1; }
    | expr                 { $$ = $1; if (!Node::root) Node::root = $1; }
    | statement statements { $$ = $1; $2->nextStatement = $1; }
    | expr      statements { $$ = $1; $2->nextStatement = $1; }
    ;
*/

statement
    : import
    | print 
    | func
    | if
    | while
    // | for
    | ret
    ;

import
    : "import" id             { $$ = Node::make<Import>($2); }
    ;

print
    : "print" expr { $$ = Node::make<Print>($2); }
    ;

func
    : "fun" id "("     ")"       "end" { $$ = Node::make<Function>($2); }
    | "fun" id "(" ids ")"       "end" { $$ = Node::make<Function>($2, $4); }
    | "fun" id "("     ")" scope "end" { $$ = Node::make<Function>($2, nullptr, $5); }
    | "fun" id "(" ids ")" scope "end" { $$ = Node::make<Function>($2, $4, $6); }
    ;

if
    : "if" expr ":"       "end"               { $$ = Node::make<If>($2); }
    | "if" expr ":" scope "end"               { $$ = Node::make<If>($2, $4); }
    | "if" expr ":"       "else"       "end"  { $$ = Node::make<If>($2); }
    | "if" expr ":"       "else" scope "end"  { $$ = Node::make<If>($2, nullptr, $5); }
    | "if" expr ":" scope "else"       "end"  { $$ = Node::make<If>($2, $4); }
    | "if" expr ":" scope "else" scope "end"  { $$ = Node::make<If>($2, $4, $6); }
    ;

while
    : "while" expr ":" scope "end" { $$ = Node::make<While>($2, $4); }
    ;

/*
for
    : "for" expr ";" expr ";" expr ":" scope "end" {}
    : "for" expr ";" expr ";" expr ":" scope "end" {}
    : "for" expr ";" expr ";" expr ":" scope "end" {}
    : "for" expr ";" expr ";" expr ":" scope "end" {}
    : "for" expr ";" expr ";" expr ":" scope "end" {}
    ;
*/

ret
    : "ret"      { $$ = Node::make<Return>(); }
    | "ret" expr { $$ = Node::make<Return>($2); }
    ;

ids
    : id                     { $$ = $1;                   }
    | ids "," id             { $$ = $1; $1->m_next = $3;  }
    ;

id
    : ID { $$ = Node::make<Id>(*$1); }
    ;

expr
    : id "=" expr            { $$ = Node::make<Assign>($1, $3);                         }
    | expr "+" expr          { $$ = Node::make<BinaryOp>(BinaryOp::ADD,        $1, $3); }
    | expr "+=" expr         { $$ = Node::make<BinaryOp>(BinaryOp::ADD_ASSIGN, $1, $3); }
    | expr "-" expr          { $$ = Node::make<BinaryOp>(BinaryOp::SUB,        $1, $3); }
    | expr "-=" expr         { $$ = Node::make<BinaryOp>(BinaryOp::SUB_ASSIGN, $1, $3); }
    | expr "*" expr          { $$ = Node::make<BinaryOp>(BinaryOp::MUL,        $1, $3); }
    | expr "*=" expr         { $$ = Node::make<BinaryOp>(BinaryOp::MUL_ASSIGN, $1, $3); }
    | expr "/" expr          { $$ = Node::make<BinaryOp>(BinaryOp::DIV,        $1, $3); }
    | expr "/=" expr         { $$ = Node::make<BinaryOp>(BinaryOp::DIV_ASSIGN, $1, $3); }
    | expr "%" expr          { $$ = Node::make<BinaryOp>(BinaryOp::MOD,        $1, $3); }
    | expr "%=" expr         { $$ = Node::make<BinaryOp>(BinaryOp::MOD_ASSIGN, $1, $3); }
    | expr ">" expr          { $$ = Node::make<BinaryOp>(BinaryOp::MORE,       $1, $3); }
    | expr ">=" expr         { $$ = Node::make<BinaryOp>(BinaryOp::MORE_EQUAL, $1, $3); }
    | expr "<" expr          { $$ = Node::make<BinaryOp>(BinaryOp::LESS,       $1, $3); }
    | expr "<=" expr         { $$ = Node::make<BinaryOp>(BinaryOp::LESS_EQUAL, $1, $3); }
    | INTEGER                { $$ = Node::make<Integer>($1);                            }
    | REAL                   { $$ = Node::make<Real>($1);                               }
    | TRUE                   { $$ = Node::make<Boolean>(true);                          }
    | FALSE                  { $$ = Node::make<Boolean>(false);                         }
    | STRING                 { $$ = Node::make<String>(*$1);                            }
    | id 
    | id "("  ")"            { $$ = Node::make<Call>($1);                               }
    | id "(" exprs ")"       { $$ = Node::make<Call>($1, $3);                           }
    ;

exprs
    : expr                   { $$ = $1; }
    | expr "," exprs         { $$ = $1; $3->m_next = $1; }
    ;

%%

#include <FunLexer.h>

int yylex(fun::FunParser::semantic_type* yylval, FunLexer& myLexer) {
    return myLexer.yylex(yylval);
}

void fun::FunParser::error(const std::string& message) {
    cerr << "error: " << message << endl;
}

