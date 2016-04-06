%{
#include <iostream>

using namespace std;
%}

%union {
    int int_token;
}

%token <int_token> QUIT HELLO SEMICOLON

%start root_node

%%

root_node: hello_node root_node | quit_node;

hello_node: HELLO SEMICOLON{
    cout << "parsed a hello node!" << endl << "Hello, user!" << endl;
};

quit_node: QUIT SEMICOLON{
    cout << "parsed a quit node!" << endl << "Goodbye, User!" << endl;
    exit(0);
};

%%
