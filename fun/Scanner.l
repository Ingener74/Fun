
%top{
// Top block
}

%{

#include <sstream>

using namespace std;

#include <Parser.hpp>
#include <Lexer.h>

#define LOCATION_FULL(startLine, startColumn, endLine, endColumn) \
	yylloc->begin.line   = startLine;   \
	yylloc->begin.column = startColumn; \
	yylloc->end.line     = endLine;     \
	yylloc->end.column   = endColumn;   \

#define LOCATION(size) \
	LOCATION_FULL(line, column, line, column + size); \
	column += size;

stringstream ss;
int str_start_line = 0, str_start_column = 0;

%}

%option noyywrap
%option c++
%option yyclass="Lexer"

digit    [0-9]
ID       [a-zA-Z_][a-zA-Z_0-9_]*

%x comment
%x strng

%%

%{
%}

"import"    { LOCATION(6); return fun::Parser::token::IMPORT;     }
"if"        { LOCATION(2); return fun::Parser::token::IF;         }
"elif"      { LOCATION(4); return fun::Parser::token::ELIF;       }
"else"      { LOCATION(4); return fun::Parser::token::ELSE;       }
"for"       { LOCATION(3); return fun::Parser::token::FOR;        }
"in"        { LOCATION(2); return fun::Parser::token::IN;         }
"while"     { LOCATION(5); return fun::Parser::token::WHILE;      }
"do"        { LOCATION(2); return fun::Parser::token::DO;         }
"print"     { LOCATION(5); return fun::Parser::token::PRINT;      }
"fun"       { LOCATION(3); return fun::Parser::token::FUN;        }
"ret"       { LOCATION(3); return fun::Parser::token::RETURN;     }
"end"       { LOCATION(3); return fun::Parser::token::END;        }
"true"      { LOCATION(4); return fun::Parser::token::TRUE;       }
"false"     { LOCATION(5); return fun::Parser::token::FALSE;      }
"nil"       { LOCATION(3); return fun::Parser::token::NIL;        }
"break"     { LOCATION(5); return fun::Parser::token::BREAK;      }
"continue"  { LOCATION(8); return fun::Parser::token::CONTINUE;   }
"try"       { LOCATION(3); return fun::Parser::token::TRY;        }
"catch"     { LOCATION(5); return fun::Parser::token::CATCH;      }
"as"        { LOCATION(2); return fun::Parser::token::AS;         }
"throw"     { LOCATION(5); return fun::Parser::token::THROW;      }
"class"     { LOCATION(5); return fun::Parser::token::CLASS;      }

":"         { LOCATION(1); return fun::Parser::token::COLON;      }
";"         { LOCATION(1); return fun::Parser::token::SEMICOLON;  }
","         { LOCATION(1); return fun::Parser::token::COMMA;      }
"."         { LOCATION(1); return fun::Parser::token::DOT;        }
"("         { LOCATION(1); return fun::Parser::token::LPAREN;     }
")"         { LOCATION(1); return fun::Parser::token::RPAREN;     }
"{"         { LOCATION(1); return fun::Parser::token::CURLYL;     }
"}"         { LOCATION(1); return fun::Parser::token::CURLYR;     }
"["         { LOCATION(1); return fun::Parser::token::SQUAREL;    }
"]"         { LOCATION(1); return fun::Parser::token::SQUARER;    }

"="         { LOCATION(1); return fun::Parser::token::ASSIGN;     }
"+"         { LOCATION(1); return fun::Parser::token::ADD;        }
"-"         { LOCATION(1); return fun::Parser::token::SUB;        }
"*"         { LOCATION(1); return fun::Parser::token::MUL;        }
"/"         { LOCATION(1); return fun::Parser::token::DIV;        }
"%"         { LOCATION(1); return fun::Parser::token::MOD;        }
">"         { LOCATION(1); return fun::Parser::token::MORE;       }
"<"         { LOCATION(1); return fun::Parser::token::LESS;       }
"+="        { LOCATION(2); return fun::Parser::token::ADD_ASSIGN; }
"-="        { LOCATION(2); return fun::Parser::token::SUB_ASSIGN; }
"*="        { LOCATION(2); return fun::Parser::token::MUL_ASSIGN; }
"/="        { LOCATION(2); return fun::Parser::token::DIV_ASSIGN; }
"%="        { LOCATION(2); return fun::Parser::token::MOD_ASSIGN; }
">="        { LOCATION(2); return fun::Parser::token::MORE_EQUAL; }
"<="        { LOCATION(2); return fun::Parser::token::LESS_EQUAL; }
"=="        { LOCATION(2); return fun::Parser::token::EQUAL;      }
"!="        { LOCATION(2); return fun::Parser::token::NOT_EQUAL;  }

{digit}+ {
    yylval->integer = atoi(yytext); 
    LOCATION(strlen(yytext));
    return fun::Parser::token::INTEGER;
}

{digit}+"."{digit}* {
    yylval->real = atof(yytext); 
    LOCATION(strlen(yytext));
    return fun::Parser::token::REAL;
}

{ID} {
    yylval->str = new string(yytext);
    LOCATION(strlen(yytext));
    return fun::Parser::token::ID;
}

\" {
    str_start_line = line;
    str_start_column = ++column;
    ss.str(""); BEGIN(strng);
}
<strng>\" {
    BEGIN(INITIAL);
    yylval->str = new string(ss.str()); 
    LOCATION_FULL(str_start_line, str_start_column, line, column)
    return fun::Parser::token::STRING;
}
<strng>\n {
	// throw std::runtime_error("error - unterminated string constant");
	ss << '\n';
	column = 0;
	line++;
}
<strng>\\[0-7]{1,3} {
	/* octal escape sequence */
	int result;
     
    (void) sscanf( yytext + 1, "%o", &result );
     
    if ( result > 0xff )
    {
    	throw std::runtime_error("error, constant is out-of-bounds");
    	ss << result;
	}
}
<strng>\\[0-9]+ {
	/* generate error - bad escape sequence; something
	*  like '\48' or '\0777777'
	*/
	throw std::runtime_error("error - bad escape sequence");
}
<strng>\\n {
	ss << '\n'; 
	column = 0; 
	line++;
}
<strng>\\t {
	ss << '\t';
	column++; 
}
<strng>\\r {
	ss << '\r';
	column++;
}
<strng>\\b {
	ss << '\b';
	column++;
}
<strng>\\f {
	ss << '\f';
	column++;
}
<strng>\\(.|\n) {
	ss << yytext[1]; column++;
}
<strng>[^\\\n\"]+ {
	char *yptr = yytext;
	while ( *yptr )
	{
		column++; 
		ss << *yptr++;
	}
}

"#"           { column++;           BEGIN(comment); }
<comment>"\n" { column = 0; line++; BEGIN(INITIAL); }
<comment>.    { column++;                           }

[ ]  { column++; };
[\t] { column++; };
[\n] { column = 0; line++; };

. { cerr << "Invalid symbol " << yytext << endl; throw std::runtime_error(std::string("Invalid symbol ") + yytext); }

%%

