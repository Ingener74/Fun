%require "3.0.4"
%skeleton "lalr1.cc"

%debug

%define api.namespace {fun}
%define parser_class_name{FunParser}

%code requires{

class FunLexer;

#include "FunAst.h"
#include "AstNode.h"

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
    
    Scope*           scope_type;
    Statement*       statement_type;
    Function*        func_type;
    Import*          import_type;
    Print*           print_type;
    If*              if_type;
    While*           while_type;
    Return*          return_type;
    Id*              id_type;    
    Expression*      expr_type;
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

%type <scope_type>        scope
%type <statement_type>    statement
%type <id_type>           id
%type <id_type>           ids
%type <expr_type>         expr
%type <expr_type>         exprs
%type <func_type>         func
%type <import_type>       import
%type <print_type>        print
%type <if_type>           if
%type <while_type>        while
%type <return_type>       ret

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
    : %empty          { $$ = ast->createNode<Scope>(); ast->setRoot($$); }
    | scope statement { $1->m_statements.push_back($2); }
    | scope expr      { $1->m_statements.push_back($2); }
    ;

statement
    : import
    | print 
    | func
    | if
    | while
    | ret
    ;

import
    : "import" id             { $$ = ast->createNode<Import>($2); }
    ;

func
    : "fun" id "("     ")"       "end" { $$ = ast->createNode<Function>($2); }
    | "fun" id "(" ids ")"       "end" { $$ = ast->createNode<Function>($2, $4); }
    | "fun" id "("     ")" scope "end" { $$ = ast->createNode<Function>($2, nullptr, $5); }
    | "fun" id "(" ids ")" scope "end" { $$ = ast->createNode<Function>($2, $4, $6); }
    ;

ids
    : id                     { $$ = $1;                   }
    | ids "," id             { $$ = $1; $1->m_next = $3;  }
    ;

id
    : ID { $$ = ast->createNode<Id>(*$1); }
    ;

ret
    : "ret"      { $$ = ast->createNode<Return>(); }
    | "ret" expr { $$ = ast->createNode<Return>($2); }
    ;

expr
    : id "=" expr            { $$ = ast->createNode<Assign>($1, $3);                         }
    | expr "+" expr          { $$ = ast->createNode<BinaryOp>(BinaryOp::ADD,        $1, $3); }
    | expr "+=" expr         { $$ = ast->createNode<BinaryOp>(BinaryOp::ADD_ASSIGN, $1, $3); }
    | expr "-" expr          { $$ = ast->createNode<BinaryOp>(BinaryOp::SUB,        $1, $3); }
    | expr "-=" expr         { $$ = ast->createNode<BinaryOp>(BinaryOp::SUB_ASSIGN, $1, $3); }
    | expr "*" expr          { $$ = ast->createNode<BinaryOp>(BinaryOp::MUL,        $1, $3); }
    | expr "*=" expr         { $$ = ast->createNode<BinaryOp>(BinaryOp::MUL_ASSIGN, $1, $3); }
    | expr "/" expr          { $$ = ast->createNode<BinaryOp>(BinaryOp::DIV,        $1, $3); }
    | expr "/=" expr         { $$ = ast->createNode<BinaryOp>(BinaryOp::DIV_ASSIGN, $1, $3); }
    | expr "%" expr          { $$ = ast->createNode<BinaryOp>(BinaryOp::MOD,        $1, $3); }
    | expr "%=" expr         { $$ = ast->createNode<BinaryOp>(BinaryOp::MOD_ASSIGN, $1, $3); }
    | expr ">" expr          { $$ = ast->createNode<BinaryOp>(BinaryOp::MORE,       $1, $3); }
    | expr ">=" expr         { $$ = ast->createNode<BinaryOp>(BinaryOp::MORE_EQUAL, $1, $3); }
    | expr "<" expr          { $$ = ast->createNode<BinaryOp>(BinaryOp::LESS,       $1, $3); }
    | expr "<=" expr         { $$ = ast->createNode<BinaryOp>(BinaryOp::LESS_EQUAL, $1, $3); }
    | INTEGER                { $$ = ast->createNode<Integer>($1);                            }
    | REAL                   { $$ = ast->createNode<Real>($1);                               }
    | TRUE                   { $$ = ast->createNode<Boolean>(true);                          }
    | FALSE                  { $$ = ast->createNode<Boolean>(false);                         }
    | STRING                 { $$ = ast->createNode<String>(*$1);                            }
    | id 
    | id "("  ")"            { $$ = ast->createNode<Call>($1);                               }
    | id "(" exprs ")"       { $$ = ast->createNode<Call>($1, $3);                           }
    ;

exprs
    : expr                   { $$ = $1; }
    | expr "," exprs         { $$ = $1; $3->m_next = $1; }
    ;

print
    : "print" expr { $$ = ast->createNode<Print>($2); }
    ;

if
    : "if" expr ":"       "end"               { $$ = ast->createNode<If>($2); }
    | "if" expr ":" scope "end"               { $$ = ast->createNode<If>($2, $4); }
    | "if" expr ":"       "else"       "end"  { $$ = ast->createNode<If>($2); }
    | "if" expr ":"       "else" scope "end"  { $$ = ast->createNode<If>($2, nullptr, $5); }
    | "if" expr ":" scope "else"       "end"  { $$ = ast->createNode<If>($2, $4); }
    | "if" expr ":" scope "else" scope "end"  { $$ = ast->createNode<If>($2, $4, $6); }
    ;

while
    : "while" expr ":" scope "end" { $$ = ast->createNode<While>($2, $4); }
    ;

%%

#include <FunLexer.h>

int yylex(fun::FunParser::semantic_type* yylval, FunLexer& myLexer) {
    return myLexer.yylex(yylval);
}

void fun::FunParser::error(const std::string& message) {
    cerr << "error: " << message << endl;
}

