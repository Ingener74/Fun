%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "y.tab.h"

using namespace std;
%}

%%

";"                 return SEMICOLON;
"hello-world"       return { cout << "got Hello, World token" << endl; return HELLO; }
"quit"              return { cout << "got Quit token" << endl; return QUIT; }

%%

int main(int argc, char* argv[]){
    for(yyFlexLexer f; f.yylex(); ){}
    return 0;
}
