%require "3.0.4"
%skeleton "lalr1.cc"

/* %defines */

%define api.namespace {myparser}

%{

#include <iostream>

using namespace std;

extern int yylex();

void yyerror(const char* );

%}

%union{
    int num;
    string* str;
}

%destructor { delete $$; /* string destructor */ } <str>

%token <num> NUM
%token <str> ID

%parse-param { char const *parsing_param };

%initial-action
{
    // Initial code
};

%%

%start root;

root : 
    NUM { 
        cout << "NUM " << $1 << endl; 
        // $$ = $1; 
    } | ID {
        cout << "ID " << $1 << endl; 
        // $$ = $1;
    };
    
// expr: ID '=' NUM { cout << "Expression " << endl; }

%%

void yyerror(const char* error){
    cerr << "error: " << error << endl;
}

int main(int argc, char* argv[]){
    cout << "MyParser" << endl;
    yyparse();
}
