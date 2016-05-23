
%top{
    // Top block
}

%{

#include <iostream>

using namespace std;

#include <FunParser.hpp>
#include <FunLexer.h>

%}

%option c++
%option noyywrap

%option yyclass="MyLexer"

DIGIT    [0-9]
ID       [a-zA-Z_][a-zA-Z_0-9]*

%%

%{
int nnn1 = 0;
%}

"import" return myparser::parser::token::IMPORT;
"if" return myparser::parser::token::IF;
"else" return myparser::parser::token::ELSE;
"for" return myparser::parser::token::FOR;
"in" return myparser::parser::token::IN;
"while" return myparser::parser::token::WHILE;
"do" return myparser::parser::token::DO;
"print" return myparser::parser::token::PRINT;
"fun" return myparser::parser::token::FUN;
"end" return myparser::parser::token::END;

":" return myparser::parser::token::COLON;
"(" return myparser::parser::token::LPAREN;
")" return myparser::parser::token::RPAREN;
"," return myparser::parser::token::COMMA;

{DIGIT}+ {
    yylval->integer = atoi(yytext); 
    return myparser::parser::token::INTEGER;
}

{DIGIT}+"."{DIGIT}* {
    yylval->real = atof(yytext); 
    return myparser::parser::token::REAL;
}

{ID} {
    yylval->str = new string(yytext);
    return myparser::parser::token::ID;
}

"="  return myparser::parser::token::ASSIGN;

"+"   { return myparser::parser::token::ADD;         }
"+="  { return myparser::parser::token::ADD_ASSIGN;  }

"-"   { return myparser::parser::token::SUB;         }
"-="  { return myparser::parser::token::SUB_ASSIGN;  }

"*"   { return myparser::parser::token::MUL;         }
"*="  { return myparser::parser::token::MUL_ASSIGN;  }

"/"   { return myparser::parser::token::DIV;         }
"/="  { return myparser::parser::token::DIV_ASSIGN;  }

"%"   { return myparser::parser::token::MOD;         }
"%="  { return myparser::parser::token::MOD_ASSIGN;  }

">"   { return myparser::parser::token::MORE;        }
">="  { return myparser::parser::token::MORE_EQUAL;  }

"<"   { return myparser::parser::token::LESS;        }
"<="  { return myparser::parser::token::LESS_EQUAL;  }

[ \t\n] ;

. { cerr << "Invalid symbol " << yytext << endl; }

%%

