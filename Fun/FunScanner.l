
%top{
    // Top block
}

%{

// #include <iostream>

using namespace std;

#include <FunParser.hpp>
#include <FunLexer.h>

%}

%option c++
%option noyywrap

%option yyclass="FunLexer"

DIGIT    [0-9]
ID       [a-zA-Z_][a-zA-Z_0-9]*

%x comment

%%

%{
int nnn1 = 0;
%}

"import"    return fun::FunParser::token::IMPORT;
"if"        return fun::FunParser::token::IF;
"elif"      return fun::FunParser::token::ELIF;
"else"      return fun::FunParser::token::ELSE;
"for"       return fun::FunParser::token::FOR;
"in"        return fun::FunParser::token::IN;
"while"     return fun::FunParser::token::WHILE;
"do"        return fun::FunParser::token::DO;
"print"     return fun::FunParser::token::PRINT;
"fun"       return fun::FunParser::token::FUN;
"ret"       return fun::FunParser::token::RETURN;
"end"       return fun::FunParser::token::END;
"true"      return fun::FunParser::token::TRUE;
"false"     return fun::FunParser::token::FALSE;
"nil"       return fun::FunParser::token::NIL;
"break"     return fun::FunParser::token::BREAK;
"continue"  return fun::FunParser::token::CONTINUE;
"try"       return fun::FunParser::token::TRY;
"catch"     return fun::FunParser::token::CATCH;
"as"        return fun::FunParser::token::AS;
"throw"     return fun::FunParser::token::THROW;
"class"     return fun::FunParser::token::CLASS;
"super"     return fun::FunParser::token::SUPER;
"self"      return fun::FunParser::token::SELF;

"__init__"  return fun::FunParser::token::INIT;
"__copy__"  return fun::FunParser::token::COPY;
"__str__"   return fun::FunParser::token::STR;
"__call__"  return fun::FunParser::token::CALL;
"__add__"   return fun::FunParser::token::ADD_METHOD;
"__sub__"   return fun::FunParser::token::SUB_METHOD;
"__mul__"   return fun::FunParser::token::MUL_METHOD;
"__div__"   return fun::FunParser::token::DIV_METHOD;
"__mod__"   return fun::FunParser::token::MOD_METHOD;
"__adda__"  return fun::FunParser::token::ADDA_METHOD;
"__suba__"  return fun::FunParser::token::SUBA_METHOD;
"__mula__"  return fun::FunParser::token::MULA_METHOD;
"__diva__"  return fun::FunParser::token::DIVA_METHOD;
"__moda__"  return fun::FunParser::token::MODA_METHOD;

":"         return fun::FunParser::token::COLON;
";"         return fun::FunParser::token::SEMICOLON;
"("         return fun::FunParser::token::LPAREN;
")"         return fun::FunParser::token::RPAREN;
","         return fun::FunParser::token::COMMA;
"."         return fun::FunParser::token::DOT;

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

"#"           { BEGIN(comment); }
<comment>"\n" { BEGIN(INITIAL); }
<comment>.    {}

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

"=="  return fun::FunParser::token::EQUAL;
"!="  return fun::FunParser::token::NOT_EQUAL;

[ \t\n] ;

. { cerr << "Invalid symbol " << yytext << endl; }

%%

