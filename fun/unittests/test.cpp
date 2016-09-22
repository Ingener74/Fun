
#include "test.h"

using namespace std;
using namespace fun;

void parse(const string& source, bool parser_debug) {
    stringstream ss;
    ss << source;
    Lexer lexer("", &ss);
    Ast ast;
    Parser parser(lexer, &ast);
    parser.set_debug_level(parser_debug);
    if (parser.parse())
        cerr << "Warning: parser.parse() not 0" << endl;
}

ParseResult parseAst(const string& source) {
    stringstream ss;
    ss << source;
    Lexer lexer("", &ss);
    unique_ptr<Ast> ast(new Ast);
    Parser parser(lexer, ast.get());
    parser.set_debug_level(0);
    if (parser.parse())
        cerr << "Warning: parser.parse() not 0" << endl;
    return {move(ast)};
}

Result interpret(const string& source) {
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
    ast->accept(interpreter.get());
    return {move(interpreter), move(debugger), move(ast)};
}

Result interpretInteractive(const string& source) {
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

