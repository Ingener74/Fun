%require "3.0.4"
%skeleton "lalr1.cc"

%debug

%define api.namespace {fun}
%define parser_class_name{FunParser}
%locations

%code requires{

class FunLexer;

#include "AST.h"

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

#define NEXT_(a, b, msg, nextWhat) { if(!a) throw std::runtime_error(msg); a->nextWhat = b; if(b) b->duplicate(); }

#define NEXT_STATEMENT(a, b)  NEXT_(a, b, "next statement error",  nextStatement)
#define NEXT_EXPRESSION(a, b) NEXT_(a, b, "next expression error", nextExpression)
#define NEXT_ID(a, b)         NEXT_(a, b, "next id error",         nextId)
#define NEXT_IF(a, b)         NEXT_(a, b, "next if error",         nextIf)
#define NEXT_ASSIGN(a, b)     NEXT_(a, b, "next assign error",     nextAssign)
#define NEXT_FUNCTION(a, b)   NEXT_(a, b, "next function error",   nextFunction)

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
    Ifs*                     ifs_type;
    If*                      if_type;
    Dictionary*              dictionary_type;
    Assign*                  assign_type;
    Class*                   class_type;
    Index*                   index_type;
}

%destructor { delete $$; } <str>

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

%token INC                   "++"
%token DEC                   "--"

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
%type <expr_type>            expr
%type <expr_type>            assign_expr
%type <assign_type>          assigns
%type <assign_type>          assign
%type <expr_type>            exprs
%type <func_type>            func
%type <func_type>            fun_expr
%type <import_type>          import
%type <print_type>           print

%type <ifs_type>             ifs
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
%parse-param { Ast* ast };

%initial-action
{
    // Initial code
};

%left "="
%left ","
%left "<" ">" "!=" "<=" ">="
%left "+" "-"
%left "*" "/"
%left "."

%%

%start program;

program
    : sttmnts { ast->setRoot($1); }
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
    : "import" ids { $$ = ast->add<Import>(@1 + @2, $2); }
    ;

print
    : "print" exprs { $$ = ast->add<Print>(@1 + @2, $2); }
    ;

func
    : "fun" id "(" ids ")" sttmnts "end" { $$ = ast->add<Function>(@1 + @7, $2, $4, $6); }
    ;

class
    : "class" id "(" ids ")" class_stmts "end" { $$ = ast->add<Class>(@1 + @7, $2, $4, $6); }
    ;

class_stmts
    : %empty             { $$ = nullptr;                    }
    | func class_stmts   { $$ = $1; NEXT_STATEMENT($1, $2); }
    | assign class_stmts { $$ = $1; NEXT_STATEMENT($1, $2); }
    ;

ifs
    : if      "end" { $$ = ast->add<Ifs>(@1 + @2, $1); }
    | if ifss "end" { $$ = ast->add<Ifs>(@1 + @3, $1); NEXT_IF($1, $2); }
    ;

ifss
    : elif      { $$ = $1; }
    | elif ifss { $$ = $1; NEXT_IF($1, $2); }
    | else      { $$ = $1; }
    ;

if
    : "if" expr ":" cycle_sttmnts { $$ = ast->add<If>(@1 + @4, $2, $4); }
    ;

elif
    : "elif" expr ":" cycle_sttmnts { $$ = ast->add<If>(@1 + @4, $2, $4); }
    ;

else
    : "else" cycle_sttmnts { $$ = ast->add<If>(@1 + @2, nullptr, $2); }
    ;

while
    : "while" expr ":" cycle_sttmnts "end" { $$ = ast->add<While>(@1 + @5, $2, $4); }
    ;

for
    : "for" expr ";" expr ";" expr ":" cycle_sttmnts "end" { $$ = ast->add<For>(@1 + @9, $2, $4, $6, $8); }
    ;

break
    : "break" { $$ = ast->add<Break>(@1); }
    ;

continue
    : "continue" { $$ = ast->add<Continue>(@1); }
    ;

ret
    : "ret" exprs  { $$ = ast->add<Return>(@1 + @2, $2); }
    ;

exception
    : "try" sttmnts "catch" ids "as" id ":" sttmnts "end" { $$ = ast->add<Exception>(@1 + @9, $2, $4, $6, $8); }
    ;

throw
    : "throw" expr { $$ = ast->add<Throw>(@1 + @2, $2); }
    ;

id
    : ID { $$ = ast->add<Id>(@1, *$1); }
    ;

ids
    : %empty       { $$ = nullptr;             }
    | id           { $$ = $1;                  }
    | id "," ids   { $$ = $1; NEXT_ID($1, $3); }
    ;

// %empty             { $$ = new Nil(); }
expr
    : assign_expr        { $$ = $1; }
    | expr "+" expr      { $$ = ast->add<BinaryOp>(@1 + @3, BinaryOp::ADD,        $1, $3); }
    | expr "-" expr      { $$ = ast->add<BinaryOp>(@1 + @3, BinaryOp::SUB,        $1, $3); }
    | expr "*" expr      { $$ = ast->add<BinaryOp>(@1 + @3, BinaryOp::MUL,        $1, $3); }
    | expr "/" expr      { $$ = ast->add<BinaryOp>(@1 + @3, BinaryOp::DIV,        $1, $3); }
    | expr "%" expr      { $$ = ast->add<BinaryOp>(@1 + @3, BinaryOp::MOD,        $1, $3); }
    | expr ">" expr      { $$ = ast->add<BinaryOp>(@1 + @3, BinaryOp::MORE,       $1, $3); }
    | expr ">=" expr     { $$ = ast->add<BinaryOp>(@1 + @3, BinaryOp::MORE_EQUAL, $1, $3); }
    | expr "<" expr      { $$ = ast->add<BinaryOp>(@1 + @3, BinaryOp::LESS,       $1, $3); }
    | expr "<=" expr     { $$ = ast->add<BinaryOp>(@1 + @3, BinaryOp::LESS_EQUAL, $1, $3); }
    | expr "==" expr     { $$ = ast->add<BinaryOp>(@1 + @3, BinaryOp::EQUAL,      $1, $3); }
    | expr "!=" expr     { $$ = ast->add<BinaryOp>(@1 + @3, BinaryOp::NOT_EQUAL,  $1, $3); }
    | INTEGER            { $$ = ast->add<Integer>(@1, $1);                                 }
    | REAL               { $$ = ast->add<Real>(@1, $1);                                    }
    | TRUE               { $$ = ast->add<Boolean>(@1, true);                               }
    | FALSE              { $$ = ast->add<Boolean>(@1, false);                              }
    | STRING             { $$ = ast->add<String>(@1, *$1);                                 }
    | NIL                { $$ = ast->add<Nil>(@1);                                         }
    | id                 { $$ = $1;                                                  }
    | expr "("  ")"      { $$ = ast->add<Call>(@1 + @3, $1);                               }
    | expr "(" exprs ")" { $$ = ast->add<Call>(@1 + @4, $1, $3);                           }
    | "(" expr ")"       { $$ = ast->add<RoundBrackets>(@1 + @3, $2);                      }
    | expr "." expr      { $$ = ast->add<Dot>(@1 + @3, $1, $3);                            }
    | fun_expr           { $$ = $1;                                                  }
    | dictionary         { $$ = $1;                                                  }
    | index              { $$ = $1;                                                  }
    ;

fun_expr
    : "fun" "(" ids ")" sttmnts "end" { $$ = ast->add<Function>(@1 + @6, nullptr, $3, $5); }
    ;

index
    : expr "[" expr "]"  { $$ = ast->add<Index>(@1 + @4, $1, $3); }
    ;

assign_expr
    : assign           { $$ = $1; }
    | exprs "+=" exprs { $$ = ast->add<Assign>(@1 + @3, $1, $3, Assign::ADD); }
    | exprs "-=" exprs { $$ = ast->add<Assign>(@1 + @3, $1, $3, Assign::SUB); }
    | exprs "*=" exprs { $$ = ast->add<Assign>(@1 + @3, $1, $3, Assign::MUL); }
    | exprs "/=" exprs { $$ = ast->add<Assign>(@1 + @3, $1, $3, Assign::DIV); }
    | exprs "%=" exprs { $$ = ast->add<Assign>(@1 + @3, $1, $3, Assign::MOD); }
    ;

assign
    : exprs "=" exprs { $$ = ast->add<Assign>(@1 + @3, $1, $3); }
    ;

assigns
    : %empty         { $$ = nullptr; }
    | assign assigns { $$ = $1; NEXT_ASSIGN($1, $2); }
    ;

dictionary
    : "{" assigns "}" { $$ = ast->add<Dictionary>(@1 + @3, $2); }
    ;

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

