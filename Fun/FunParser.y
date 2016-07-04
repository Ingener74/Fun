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
    
    Statement*            sttmnt_type;
    Function*             func_type;
    Import*               import_type;
    Print*                print_type;
    If*                   if_type;
    While*                while_type;
    For*                  for_type;
    Return*               return_type;
    Id*                   id_type;    
    Expression*           expr_type;
    Break*                break_type;
    Continue*             continue_type;
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

%token EQUAL              "=="
%token NOT_EQUAL          "!="

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
%token NIL                "null"
%token BREAK              "break"
%token CONTINUE           "continue"

%type <sttmnt_type>       program
%type <sttmnt_type>       sttmnt
%type <sttmnt_type>       sttmnts
%type <sttmnt_type>       cycle_sttmnt
%type <sttmnt_type>       cycle_sttmnts
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
%type <break_type>        break
%type <continue_type>     continue

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

%start program;

program
    : sttmnts { Statement::entryPoint = $1; }
    ;

sttmnts
    : %empty           { $$ = nullptr; }
    | sttmnt sttmnts   { $$ = $1; $1->nextStatement = $2; }
    ;

sttmnt
    : import    { $$ = $1; }
    | print     { $$ = $1; }
    | func      { $$ = $1; }
    | if        { $$ = $1; }
    | while     { $$ = $1; }
    | for       { $$ = $1; }
    | ret       { $$ = $1; }
    | expr      { $$ = $1; }
    ;

cycle_sttmnts
    : %empty                        { $$ = nullptr; }
    | sttmnt        cycle_sttmnts   { $$ = $1; $1->nextStatement = $2; }
    | cycle_sttmnt  cycle_sttmnts   { $$ = $1; $1->nextStatement = $2; }
    ;

cycle_sttmnt
    : break    { $$ = $1; }
    | continue { $$ = $1; }
    ;

import
    : "import" ids { $$ = Statement::make<Import>($2); }
    ;

print
    : "print" exprs { $$ = Statement::make<Print>($2); }
    ;

func
    : "fun" id "(" ids ")" sttmnts "end"   { $$ = Statement::make<Function>($2, $4, $6); }
    ;

if
    : "if" expr ":" cycle_sttmnts "end"                       { $$ = Statement::make<If>($2, $4);     }
    | "if" expr ":" cycle_sttmnts "else" cycle_sttmnts "end"  { $$ = Statement::make<If>($2, $4, $6); }
    ;

while
    : "while" expr ":" cycle_sttmnts "end" { $$ = Statement::make<While>($2, $4); }
    ;

for
    : "for" expr ";" expr ";" expr ":" cycle_sttmnts "end"   { $$ = Statement::make<For>($2, $4, $6, $8); }
    ;

break
    : "break" { $$ = Statement::make<Break>(); }
    ;

continue
    : "continue" { $$ = Statement::make<Continue>(); }
    ;

ret
    : "ret"        { $$ = Statement::make<Return>();   } // check useless
    | "ret" exprs  { $$ = Statement::make<Return>($2); }
    ;

ids
    : %empty       { $$ = nullptr;              }
    | id           { $$ = $1;                   }
    | id "," ids   { $$ = $1; $1->nextId = $3;  }
    ;

id
    : ID { $$ = Statement::make<Id>(*$1); }
    ;

expr
    : %empty             { $$ = nullptr; }
    | id "=" expr        { $$ = Statement::make<Assign>($1, $3);                         }
    | expr "+" expr      { $$ = Statement::make<BinaryOp>(BinaryOp::ADD,        $1, $3); }
    | expr "+=" expr     { $$ = Statement::make<BinaryOp>(BinaryOp::ADD_ASSIGN, $1, $3); }
    | expr "-" expr      { $$ = Statement::make<BinaryOp>(BinaryOp::SUB,        $1, $3); }
    | expr "-=" expr     { $$ = Statement::make<BinaryOp>(BinaryOp::SUB_ASSIGN, $1, $3); }
    | expr "*" expr      { $$ = Statement::make<BinaryOp>(BinaryOp::MUL,        $1, $3); }
    | expr "*=" expr     { $$ = Statement::make<BinaryOp>(BinaryOp::MUL_ASSIGN, $1, $3); }
    | expr "/" expr      { $$ = Statement::make<BinaryOp>(BinaryOp::DIV,        $1, $3); }
    | expr "/=" expr     { $$ = Statement::make<BinaryOp>(BinaryOp::DIV_ASSIGN, $1, $3); }
    | expr "%" expr      { $$ = Statement::make<BinaryOp>(BinaryOp::MOD,        $1, $3); }
    | expr "%=" expr     { $$ = Statement::make<BinaryOp>(BinaryOp::MOD_ASSIGN, $1, $3); }
    | expr ">" expr      { $$ = Statement::make<BinaryOp>(BinaryOp::MORE,       $1, $3); }
    | expr ">=" expr     { $$ = Statement::make<BinaryOp>(BinaryOp::MORE_EQUAL, $1, $3); }
    | expr "<" expr      { $$ = Statement::make<BinaryOp>(BinaryOp::LESS,       $1, $3); }
    | expr "<=" expr     { $$ = Statement::make<BinaryOp>(BinaryOp::LESS_EQUAL, $1, $3); }
    | expr "==" expr     { $$ = Statement::make<BinaryOp>(BinaryOp::EQUAL,      $1, $3); }
    | expr "!=" expr     { $$ = Statement::make<BinaryOp>(BinaryOp::NOT_EQUAL,  $1, $3); }
    | INTEGER            { $$ = Statement::make<Integer>($1);                            }
    | REAL               { $$ = Statement::make<Real>($1);                               }
    | TRUE               { $$ = Statement::make<Boolean>(true);                          }
    | FALSE              { $$ = Statement::make<Boolean>(false);                         }
    | STRING             { $$ = Statement::make<String>(*$1);                            }
    | NIL                { $$ = Statement::make<Null>();                                 }
    | id                 { $$ = $1;                                                      }
    | id "("  ")"        { $$ = Statement::make<Call>($1);                               } // check useless
    | id "(" exprs ")"   { $$ = Statement::make<Call>($1, $3);                           }
    ;

exprs
    : expr             { $$ = $1; }
    | expr "," exprs   { $$ = $1; $1->nextExpression = $3; }
    ;

%%

#include <FunLexer.h>

int yylex(fun::FunParser::semantic_type* yylval, FunLexer& myLexer) {
    return myLexer.yylex(yylval);
}

void fun::FunParser::error(const std::string& message) {
    cerr << "error: " << message << endl;
}

