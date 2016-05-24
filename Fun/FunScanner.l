
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

%option yyclass="FunLexer"

DIGIT    [0-9]
ID       [a-zA-Z_][a-zA-Z_0-9]*

%%

%{
int nnn1 = 0;
%}

"import"  return fun::FunParser::token::IMPORT;
"if"      return fun::FunParser::token::IF;
"else"    return fun::FunParser::token::ELSE;
"for"     return fun::FunParser::token::FOR;
"in"      return fun::FunParser::token::IN;
"while"   return fun::FunParser::token::WHILE;
"do"      return fun::FunParser::token::DO;
"print"   return fun::FunParser::token::PRINT;
"fun"     return fun::FunParser::token::FUN;
"ret"     return fun::FunParser::token::RETURN;
"end"     return fun::FunParser::token::END;
"true"    return fun::FunParser::token::TRUE;
"false"   return fun::FunParser::token::FALSE;

":"       return fun::FunParser::token::COLON;
"("       return fun::FunParser::token::LPAREN;
")"       return fun::FunParser::token::RPAREN;
","       return fun::FunParser::token::COMMA;

{DIGIT}+ {
    yylval->integer = atoi(yytext); 
    return fun::FunParser::token::INTEGER;
}

{DIGIT}+"."{DIGIT}* {
    yylval->real = atof(yytext); 
    return fun::FunParser::token::REAL;
}

{ID} {
    yylval->str = new string(yytext);
    return fun::FunParser::token::ID;
}

["][^"]*["] {
    yylval->str = new string(yytext + 1, yyleng - 2);
    return fun::FunParser::token::STRING;
}

[#][^#\n]*[\n] { /* comment*/ }

"="   return fun::FunParser::token::ASSIGN;

"+"   return fun::FunParser::token::ADD;
"+="  return fun::FunParser::token::ADD_ASSIGN;

"-"   return fun::FunParser::token::SUB;
"-="  return fun::FunParser::token::SUB_ASSIGN;

"*"   return fun::FunParser::token::MUL;
"*="  return fun::FunParser::token::MUL_ASSIGN;

"/"   return fun::FunParser::token::DIV;
"/="  return fun::FunParser::token::DIV_ASSIGN;

"%"   return fun::FunParser::token::MOD;
"%="  return fun::FunParser::token::MOD_ASSIGN;

">"   return fun::FunParser::token::MORE;
">="  return fun::FunParser::token::MORE_EQUAL;

"<"   return fun::FunParser::token::LESS;
"<="  return fun::FunParser::token::LESS_EQUAL;

[ \t\n] ;

. { cerr << "Invalid symbol " << yytext << endl; }

%%

