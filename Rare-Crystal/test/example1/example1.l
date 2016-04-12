%option nodefault
%option noyywrap
%option c++

%{
#include <iostream>

using namespace std;

enum tokType {
    ID        = 258,
    NUMBER    = 259,
    ADD       = 260,
    SUB       = 261,
    MUL       = 262,
    DIV       = 263,
    ASSIGN    = 264,
    EOL       = 265, // end of line
    EOE       = 266,
};

%}

%%

[0-9]+ {
    cout << "NUMBER " << yytext << " ";
    yylval = atoi(yytext); 
    return NUMBER;
}
[a-zA-Z]+ {
    cout << "VARIABLE " << yytext << " ";
    return ID;
}
";" {
    cout << "TERMINATE " << yytext << " ";
    return EOE;
}
"+" {
    cout << "PLUS " << yytext << " ";
    return ADD;
}
"-" {
    cout << "PLUS " << yytext << " ";
    return SUB;
}
"*" {
    cout << "PLUS " << yytext << " ";
    return MUL;
}
"/" {
    cout << "PLUS " << yytext << " ";
    return DIV;
}
"=" {
    cout << "ASSIGN " << yytext << " ";
    return ASSIGN;
}
"\n" {
    cout << "NEW LINE ";
    return EOL;
}
. ;

%%

int main(int argc, char* argv[]){
    yyFlexLexer f;
    int tok;
    while(tok = f.yylex()){
        cout << "tok " << tok << endl;
    }
    return 0;
}
