%option noyywrap

%{
#include <iostream>

using namespace std;
%}

%%

[0-9]+ {
    cout << "NUMBER " << yytext << " ";
}
[a-zA-Z]+ {
    cout << "VARIABLE " << yytext << " ";
}
; {
    cout << "TERMINATE " << yytext << " ";
}
\+ {
    cout << "PLUS " << yytext << " ";
}
= {
    cout << "ASSIGN " << yytext << " ";
}
\n {
    cout << "NEW LINE " << yytext << endl;
}
. ;

%%

int main(int argc, char* argv[]){
    for(yyFlexLexer f; f.yylex(); ){}
    return 0;
}