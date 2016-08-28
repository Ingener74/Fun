
#include "test.h"

using namespace std;
using namespace fun;

bool parse(const std::string& source, bool parser_debug) {
    stringstream ss;
    ss << source;
    Lexer lexer("", &ss);
    Ast ast;
    Parser parser(lexer, &ast);
    parser.set_debug_level(parser_debug);
    int result = parser.parse();
    return result == 0;
}

ParseResult parseAst(const std::string& source) {
    stringstream ss;
    ss << source;
    Lexer lexer("", &ss);
    std::unique_ptr<Ast> ast(new Ast);
    Parser parser(lexer, ast.get());
    parser.set_debug_level(0);
    int result = parser.parse();
    return {result == 0, move(ast)};
}

Result interpret(const std::string& source) {
    std::unique_ptr<Debugger> debugger(new DebuggerMock);
    std::unique_ptr<Interpreter> interpreter(new Interpreter(debugger.get()));
    std::unique_ptr<Ast> ast(new Ast);
    stringstream ss;
    ss << source;
    Lexer lexer("", &ss);
    Parser parser(lexer, ast.get());
    parser.set_debug_level(0);
    bool result = parser.parse();
    ast->accept(interpreter.get());
    return {move(interpreter), move(debugger), move(ast)};
}

