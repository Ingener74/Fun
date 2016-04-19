%require "3.0.4"
%skeleton "lalr1.cc"

/* %defines */

%define api.namespace {myparser}

%code requires{
class MyLexer;
// #include <MyLexer.h>
}

%{

#include <iostream>

using namespace std;

void yyerror(const char* );

%}

%union{
    int num;
    std::string* str;
}

%destructor { delete $$; /* string destructor */ } <str>

%code{
int yylex(myparser::parser::semantic_type* , MyLexer&);
}

%token <num> NUM
%token <str> ID
%token END 0

%param{ MyLexer& myLexer };
// %parse-param { char const *parsing_param };

%initial-action
{
    // Initial code
};

%%

%start root;

root
    : %empty { cout << "empty" << endl; } 
    | NUM { cout << "NUM " << $1 << endl; /* $$ = $1; */  } 
    | ID { cout << "ID " << $1 << endl; /* $$ = $1; */ };

%%

#include <fstream>
#include <MyLexer.h>

int yylex(myparser::parser::semantic_type* yylval, MyLexer& myLexer){
    return myLexer.yylex(yylval);
}

void myparser::parser::error(const std::string& message){
    cerr << "error: " << message << endl;
}

int main(int argc, char* argv[]){
    cout << "MyParser" << endl;

    try {
        if(argc < 2)
            throw std::runtime_error("no files");
        
        ifstream file(argv[1]);
        
        MyLexer myLexer(&file);
        myparser::parser prsr(myLexer);
        prsr.parse();

        return 0;
    } catch (const std::exception& e){
        cerr << "error: " << e.what() << endl;
        return 1;
    }
}


