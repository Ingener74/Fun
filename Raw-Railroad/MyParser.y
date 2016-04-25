%require "3.0.4"
%skeleton "lalr1.cc"

/* %defines */

%define api.namespace {myparser}

%code requires{
class MyLexer;

//class MyAst;

#include "MyAst.h"

#include "Expr.h"
#include "AssignExpr.h"
#include "IdExpr.h"
#include "NumExpr.h"
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
}

%destructor { delete $$; /* string destructor */ } <str> <expr_type>

%code{
int yylex(myparser::parser::semantic_type* , MyLexer&);
}

%token <num> NUM
%token <str> ID
%token EOL
%token <chr> ASSIGN "="

%type <expr_type> expr

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
    | root line
    ;

line
    : EOL
    | expr EOL { cout << $1->toString() << endl; }
    ;

expr
    : ID "=" NUM { $$ = new AssignExpr(*$1, $3); myAst->addVariable(*$1, $3); }
    // | ID         { $$ = new IdExpr(*$1); }
    // | NUM        { $$ = new NumExpr($1); }
    ;

%%

// #include <fstream>
#include <MyLexer.h>
// #include <MyAst.h>

int yylex(myparser::parser::semantic_type* yylval, MyLexer& myLexer){
    return myLexer.yylex(yylval);
}

void myparser::parser::error(const std::string& message){
    cerr << "error: " << message << endl;
}

/*
int main(int argc, char* argv[]){
    cout << "MyParser" << endl;

    try {
        if(argc < 2)
            throw std::runtime_error("no files");
        
        ifstream file(argv[1]);
        
        MyLexer myLexer(&file);
        myparser::parser prsr(myLexer);
        prsr.parse();

        return 0;
    } catch (const std::exception& e){
        cerr << "error: " << e.what() << endl;
        return 1;
    }
}
*/

