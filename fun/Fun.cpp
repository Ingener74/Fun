#include <fstream>
#include "Fun.h"

namespace fun {

using namespace std;
using namespace Poco;

Fun::Fun() {
}

Fun::~Fun() {
}

AutoPtr<Pot> Fun::parseString(const string& source) {
    stringstream ss;
    ss << source;
    return parseStream(ss);
}

AutoPtr<Pot> Fun::parseStream(const istream& source) {
    AutoPtr<Pot> pot;
    Lexer lexer("", &source);
    Parser parser(lexer, pot);
    parser.set_debug_level(0);
    if (parser.parse())
        throw FunError("Warning: parser.parse() not 0");
    return pot;
}

AutoPtr<Pot> Fun::parseFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open())
        throw FunError(string("can't open file ") + filename);
    return parseStream(file);
}

void Fun::evalString(const string& script) {
    evalAst(parseString(script));
}

void Fun::evalStream(const istream& script) {
    evalAst(parseStream(script));
}

void Fun::evalFile(const string& filename) {
    evalAst(parseFile(filename));
}

void Fun::evalAst(AutoPtr<Pot> pot) {
    _debugger->listen(_visitor, pot);
}

Fun& Fun::setDebugger(DebuggerType debugger) {
#ifdef FUN_UNITTESTS
//        TestingMockDebugger
#endif
    return *this;
}

AutoPtr<Debugger> Fun::getDebugger() {
    return _debugger;
}

}
