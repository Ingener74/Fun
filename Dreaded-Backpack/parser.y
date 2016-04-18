
%{

#include <iostream>
#include <string>

using namespace std;

Root* g_root;

%}

%union {
    string* str;
    int integer;
    double real;
    
}

%token <integer> TINT;
%token <real> TDOUBLE;
%token <str> TID;

%type <>root;

%start program;

%%

program: | statements 
    {
        cout << $1 << endl;
        g_root = $1; 
    }
    ;
    
statements: 
    statement
        {
            cout << "" << endl;
            $$ = new Statement($1);
        }
    | statements statement 
        {
        }
    ;

%%
