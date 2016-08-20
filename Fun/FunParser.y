%require "3.0.4"
%skeleton "lalr1.cc"

%debug

%define api.namespace {fun}
%define parser_class_name{FunParser}
%locations

%code requires{

class FunLexer;

#include "Nodes.h"

// POCO compability
#undef IN
#undef TRUE
#undef FALSE
// POCO compability

}

%{
#include <iostream>
using namespace std;
void yyerror(const char* );

#define NEXT_STATEMENT(a, b)  if(!a) throw std::runtime_error("next statement error");  a->nextStatement = b;
#define NEXT_EXPRESSION(a, b) if(!a) throw std::runtime_error("next expression error"); a->nextExpression =  b;
#define NEXT_ID(a, b)         if(!a) throw std::runtime_error("next id error");         a->nextId = b;
#define NEXT_IF(a, b)         if(!a) throw std::runtime_error("next if error");         a->nextIf = b;
#define NEXT_ASSIGN(a, b)     if(!a) throw std::runtime_error("next assign error");     a->nextAssign = b;
#define NEXT_FUNCTION(a, b)   if(!a) throw std::runtime_error("next function error");   a->nextFunction = b;

%}

%union{
    long long int            integer;
    double                   real;
    std::string*             str;
    
    Statement*               sttmnt_type;
    Function*                func_type;
    Import*                  import_type;
    Print*                   print_type;
    While*                   while_type;
    For*                     for_type;
    Return*                  return_type;
    Id*                      id_type;    
    Expression*              expr_type;
    Break*                   break_type;
    Continue*                continue_type;
    Exception*               exception_type;
    Throw*                   throw_type;
    If*                      if_type;
    Dictionary*              dictionary_type;
    Assign*                  assign_type;
    Class*                   class_type;
    Index*                   index_type;
}

// %destructor { delete $$; } <str> <scope_type> <import_type> <expr_type> <print_type> <func_type> <arg_type> <if_type> <expr_list_type> <id_type> <statement_type> <while_type>

%code{
int yylex(fun::FunParser::semantic_type*, fun::location*, FunLexer&);
}

%token <integer>             INTEGER
%token <real>                REAL
%token <str>                 ID
%token <str>                 STRING
%token EOL

%token ASSIGN                "="

%token ADD_ASSIGN            "+="
%token SUB_ASSIGN            "-="
%token MUL_ASSIGN            "*="
%token DIV_ASSIGN            "/="
%token MOD_ASSIGN            "%="
   
%token ADD                   "+"
%token SUB                   "-"
%token MUL                   "*"
%token DIV                   "/"
%token MOD                   "%"

%token INC "++"
%token DEC "--"

/*
++   --         Суффиксальный/постфиксный инкремент и декремент
.               Выбор элемента по ссылке
++   --         Префиксный инкремент и декремент    Справа-налево
+   −           Унарный плюс и минус
!   ~           Логическое НЕ и побитовое НЕ
*   /   %       Умножение, деление и остаток
+   −           Сложение и вычитание
<<   >>         Побитовый сдвиг влево и сдвиг вправо
&               Побитовое И
^               Побитовый XOR (исключающее или)
|               Побитовое ИЛИ (inclusive or)
&&              Логическое И
||              Логическое ИЛИ
?:              Тернарное условие   Справа-налево
=               Прямое присваивание (предоставляемое по умолчанию для C++ классов)
+=   −=         Присвоение с суммированием и разностью
*=   /=   %=    Присвоение с умножением, делением и остатком от деления
<<=   >>=       Присвоение с побитовым сдвигом слево и вправо
&=   ^=   |=    Присвоение с побитовыми логическими операциями (И, XOR, ИЛИ)
throw           Throw оператор (выброс исключений)
,
*/

%token MORE                  ">"
%token MORE_EQUAL            ">="

%token LESS                  "<"
%token LESS_EQUAL            "<="

%token EQUAL                 "=="
%token NOT_EQUAL             "!="

%token COLON                 ":"
%token SEMICOLON             ";"
%token COMMA                 ","
%token DOT                   "."
%token CURLYL                "{"
%token CURLYR                "}"
%token SQUAREL               "["
%token SQUARER               "]"
%token LPAREN                "("
%token RPAREN                ")"

%token IMPORT                "import"
%token IF                    "if"
%token ELIF                  "elif"
%token ELSE                  "else"
%token FOR                   "for"
%token IN                    "in"
%token WHILE                 "while"
%token DO                    "do"
%token FUN                   "fun"
%token PRINT                 "print"
%token RETURN                "ret"
%token END                   "end"
%token TRUE                  "true"
%token FALSE                 "false"
%token NIL                   "nil"
%token BREAK                 "break"
%token CONTINUE              "continue"
%token TRY                   "try"
%token CATCH                 "catch"
%token AS                    "as"
%token THROW                 "throw"
%token CLASS                 "class"

%type <sttmnt_type>          program
%type <sttmnt_type>          sttmnt
%type <sttmnt_type>          sttmnts
%type <sttmnt_type>          cycle_sttmnt
%type <sttmnt_type>          cycle_sttmnts
%type <id_type>              id
%type <id_type>              ids
// %type <expr_type>            dots
%type <expr_type>            expr
%type <expr_type>            assign_expr
%type <assign_type>          assigns
%type <assign_type>          assign
%type <expr_type>            exprs
%type <func_type>            func
%type <func_type>            fun_expr
%type <import_type>          import
%type <print_type>           print

%type <if_type>              ifs
%type <if_type>              ifss
%type <if_type>              if
%type <if_type>              elif
%type <if_type>              else

%type <while_type>           while
%type <for_type>             for
%type <return_type>          ret
%type <break_type>           break
%type <continue_type>        continue
%type <exception_type>       exception
%type <throw_type>           throw
%type <dictionary_type>      dictionary
%type <class_type>           class
%type <sttmnt_type>          class_stmts
%type <index_type>           index

%param { FunLexer& myLexer };
// %parse-param { fun::FunAst* ast };

%initial-action
{
    // Initial code
};

%left "="
%left ","
%left "<" ">" "!=" "<=" ">="
%left "+" "-"
%left "*" "/"

%%

%start program;

program
    : sttmnts { Statement::entryPoint = $1; }
    ;

sttmnts
    : %empty           { $$ = nullptr; }
    | sttmnt sttmnts   { $$ = $1; NEXT_STATEMENT($1, $2) }
    ;

sttmnt
    : import       { $$ = $1; }
    | print        { $$ = $1; }
    | func         { $$ = $1; }
    | ifs          { $$ = $1; }
    | while        { $$ = $1; }
    | for          { $$ = $1; }
    | ret          { $$ = $1; }
    | expr         { $$ = $1; }
    | exception    { $$ = $1; }
    | throw        { $$ = $1; }
    | class        { $$ = $1; }
    ;

cycle_sttmnts
    : %empty                        { $$ = nullptr; }
    | sttmnt        cycle_sttmnts   { $$ = $1; NEXT_STATEMENT($1, $2); }
    | cycle_sttmnt  cycle_sttmnts   { $$ = $1; NEXT_STATEMENT($1, $2); }
    ;

cycle_sttmnt
    : break    { $$ = $1; }
    | continue { $$ = $1; }
    ;

import
    : "import" ids { $$ = new Import(@1 + @2, $2); }
    ;

print
    : "print" exprs { $$ = new Print(@1 + @2, $2); }
    ;

func
    : "fun" id "(" ids ")" sttmnts "end" { $$ = new Function(@1 + @7, $2, $4, $6); }
    ;

class
    : "class" id "(" ids ")" class_stmts "end" { $$ = new Class(@1 + @7, $2, $4, $6); }
    ;

class_stmts
    : %empty             { $$ = nullptr;                    }
    | func class_stmts   { $$ = $1; NEXT_STATEMENT($1, $2); }
    | assign class_stmts { $$ = $1; NEXT_STATEMENT($1, $2); }
    ;

ifs
    : if      "end" { $$ = $1; }
    | if ifss "end" { $$ = $1; NEXT_IF($1, $2); }
    ;

ifss
    : elif      { $$ = $1; }
    | elif ifss { $$ = $1; NEXT_IF($1, $2); }
    | else      { $$ = $1; }
    ;

if
    : "if" expr ":" cycle_sttmnts { $$ = new If(@1 + @4, $2, $4); }
    ;

elif
    : "elif" expr ":" cycle_sttmnts { $$ = new If(@1 + @4, $2, $4); }
    ;

else
    : "else" cycle_sttmnts { $$ = new If(@1 + @2, nullptr, $2); }
    ;

while
    : "while" expr ":" cycle_sttmnts "end" { $$ = new While(@1 + @5, $2, $4); }
    ;

for
    : "for" expr ";" expr ";" expr ":" cycle_sttmnts "end" { $$ = new For(@1 + @9, $2, $4, $6, $8); }
    ;

break
    : "break" { $$ = new Break(@1); }
    ;

continue
    : "continue" { $$ = new Continue(@1); }
    ;

ret
    : "ret" exprs  { $$ = new Return(@1 + @2, $2); }
    ;

exception
    : "try" sttmnts "catch" ids "as" id ":" sttmnts "end" { $$ = new Exception(@1 + @9, $2, $4, $6, $8); }
    ;

throw
    : "throw" expr { $$ = new Throw(@1 + @2, $2); }
    ;

id
    : ID { $$ = new Id(@1, *$1); }
    ;

ids
    : %empty       { $$ = nullptr;             }
    | id           { $$ = $1;                  }
    | id "," ids   { $$ = $1; NEXT_ID($1, $3); }
    ;

// %empty             { $$ = new Nil(); }
expr
    : assign_expr        { $$ = $1; }
    | expr "+" expr      { $$ = new BinaryOp(@1 + @3, BinaryOp::ADD,        $1, $3); }
    | expr "-" expr      { $$ = new BinaryOp(@1 + @3, BinaryOp::SUB,        $1, $3); }
    | expr "*" expr      { $$ = new BinaryOp(@1 + @3, BinaryOp::MUL,        $1, $3); }
    | expr "/" expr      { $$ = new BinaryOp(@1 + @3, BinaryOp::DIV,        $1, $3); }
    | expr "%" expr      { $$ = new BinaryOp(@1 + @3, BinaryOp::MOD,        $1, $3); }
    | expr ">" expr      { $$ = new BinaryOp(@1 + @3, BinaryOp::MORE,       $1, $3); }
    | expr ">=" expr     { $$ = new BinaryOp(@1 + @3, BinaryOp::MORE_EQUAL, $1, $3); }
    | expr "<" expr      { $$ = new BinaryOp(@1 + @3, BinaryOp::LESS,       $1, $3); }
    | expr "<=" expr     { $$ = new BinaryOp(@1 + @3, BinaryOp::LESS_EQUAL, $1, $3); }
    | expr "==" expr     { $$ = new BinaryOp(@1 + @3, BinaryOp::EQUAL,      $1, $3); }
    | expr "!=" expr     { $$ = new BinaryOp(@1 + @3, BinaryOp::NOT_EQUAL,  $1, $3); }
    | INTEGER            { $$ = new Integer(@1, $1);                                 }
    | REAL               { $$ = new Real(@1, $1);                                    }
    | TRUE               { $$ = new Boolean(@1, true);                               }
    | FALSE              { $$ = new Boolean(@1, false);                              }
    | STRING             { $$ = new String(@1, *$1);                                 }
    | NIL                { $$ = new Nil(@1);                                         }
    | id                 { $$ = $1;                                                  }
    | expr "("  ")"      { $$ = new Call(@1 + @3, $1);                               }
    | expr "(" exprs ")" { $$ = new Call(@1 + @4, $1, $3);                           }
    | "(" expr ")"       { $$ = new RoundBrackets(@1 + @3, $2);                      }
    // | dots               { $$ = $1; }
    | fun_expr           { $$ = $1; }
    | dictionary         { $$ = $1; }
    | index              { $$ = $1; }
    ;

fun_expr
    : "fun" "(" ids ")" sttmnts "end" { $$ = new Function(@1 + @6, nullptr, $3, $5); }
    ;

index
    : expr "[" expr "]"  { $$ = new Index(@1 + @4, $1, $3); }
    ;

assign_expr
    : assign           { $$ = $1; }
    | exprs "+=" exprs { $$ = new Assign(@1 + @3, $1, $3, Assign::ADD); }
    | exprs "-=" exprs { $$ = new Assign(@1 + @3, $1, $3, Assign::SUB); }
    | exprs "*=" exprs { $$ = new Assign(@1 + @3, $1, $3, Assign::MUL); }
    | exprs "/=" exprs { $$ = new Assign(@1 + @3, $1, $3, Assign::DIV); }
    | exprs "%=" exprs { $$ = new Assign(@1 + @3, $1, $3, Assign::MOD); }
    ;

assign
    : exprs "=" exprs { $$ = new Assign(@1 + @3, $1, $3); }
    ;

assigns
    : %empty         { $$ = nullptr; }
    | assign assigns { $$ = $1; NEXT_ASSIGN($1, $2); }
    ;

dictionary
    : "{" assigns "}" { $$ = new Dictionary(@1 + @3, $2); }
    ;

/*
dots
    : expr "." dots { $$ = $1; NEXT_EXPRESSION($1, $3); }
    ;
*/

exprs
    : expr             { $$ = $1; }
    | expr "," exprs   { $$ = $1; NEXT_EXPRESSION($1, $3); }
    ;

%%

#include <FunLexer.h>

int yylex(fun::FunParser::semantic_type* yylval, fun::location* yylloc, FunLexer& myLexer) {
    return myLexer.yylex(yylval, yylloc);
}

void fun::FunParser::error(const location& loc, const std::string& message) {
    cerr << "error: " << loc << ": " << message << endl;
}

