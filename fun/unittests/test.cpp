#include "test.h"

using namespace std;
using namespace fun;

Result parse(const string& source) {
    stringstream ss;
    ss << source;
    Lexer lexer("", &ss);
    unique_ptr<Ast> ast(new Ast);
    Parser parser(lexer, ast.get());
    parser.set_debug_level(0);
    if (parser.parse())
        cerr << "Warning: parser.parse() not 0" << endl;
    return {{}, {}, move(ast)};
}

Result eval(const string& source) {
    unique_ptr<DebuggerMock> debugger(new DebuggerMock);
    unique_ptr<Interpreter> interpreter(new Interpreter(debugger.get()));
    unique_ptr<Ast> ast(new Ast);
    stringstream ss;
    ss << source;
    Lexer lexer("", &ss);
    Parser parser(lexer, ast.get());
    parser.set_debug_level(0);
    if (parser.parse())
        cerr << "Warning: parser.parse() not 0" << endl;
    return {move(interpreter), move(debugger), move(ast)};
}

