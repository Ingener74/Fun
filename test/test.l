%{

int yylex(void);
int yywrap(void){}

%}

%%
[0-9]+ {
    printf("NUMBER %s\n", yytext);
}
[a-zA-Z]+ {
    printf("VARIABLE %s\n", yytext);
}
; {
    printf("TERMINATE %s\n", yytext);
}
\+ {
    printf("PLUS %s\n", yytext);
}
= {
    printf("ASSIGN %s\n", yytext);
}
\n {
    printf("NEW LINE %s\n", yytext);
}
. ;
%%

int main(int argc, char* argv[]){
    yylex();
    return 0;
}