#include "test.h"
#include "Utils.h"

using namespace std;
using namespace fun;

Result parse(const string& source) {
    auto debugger = make_unique_<DebuggerMock>();
    auto interpreter = make_unique_<Interpreter>(debugger.get());
    auto ast = make_unique_<Ast>();
    stringstream ss;
    ss << source;
    Lexer lexer("", &ss);
    Parser parser(lexer, ast.get());
    parser.set_debug_level(0);
    if (parser.parse())
        cerr << "Warning: parser.parse() not 0" << endl;
    return {move(interpreter), move(debugger), move(ast)};
}

