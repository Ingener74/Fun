#include <fstream>
#include "debuggers/EmptyDebugger.h"
#include "debuggers/CommandLineDebugger.h"
#include "debuggers/TcpSocketDebugger.h"
#include "Compiler.h"
#include "Fun.h"

namespace fun {

using namespace std;
using namespace Poco;

Fun::Fun() {
//    _visitor = new Interpreter;
    _visitor = new Compiler;
}

Fun::~Fun() {
}

AutoPtr<Pot> Fun::parseString(const string& source) {
    stringstream ss;
    ss << source;
    return parseStream(ss);
}

AutoPtr<Pot> Fun::parseStream(istream& source) {
    AutoPtr<Pot> pot(new Pot);
    Lexer lexer(_filename, source);
    Parser parser(lexer, pot);
    if (parser.parse())
        throw FunError("Warning: parser.parse() not 0");
    return pot;
}

AutoPtr<Pot> Fun::parseFile(const string& filename) {
    _filename = filename;
    ifstream file(_filename);
    if (!file.is_open())
        throw FunError(string("can't open file ") + _filename);
    return parseStream(file);
}

void Fun::evalString(const string& script) {
    evalAst(parseString(script));
}

void Fun::evalStream(istream& script) {
    evalAst(parseStream(script));
}

void Fun::evalFile(const string& filename) {
    evalAst(parseFile(filename));
}

void Fun::evalAst(AutoPtr<Pot> pot) {
//    _visitor.cast<Interpreter>()->setDebugger(_debugger);
    pot->accept(_visitor);
//    _debugger->listen(_visitor, pot);
    _virtualMachine.run(_visitor.cast<Compiler>()->getProgram(), pot);
}

Fun& Fun::setDebugger(DebuggerType debugger) {

    switch (debugger) {
    case DebuggerType::NoDebugger:
        _debugger = new EmptyDebugger;
        break;
    case DebuggerType::CommandLineDebugger:
        _debugger = new CommandLineDebugger;
        break;
    case DebuggerType::NetDebugger:
        _debugger = new TcpSocketDebugger;
        break;
    default:
        throw FunError("invalid debugger type");
    }
    return *this;
}

Fun& Fun::setDebugger(Poco::AutoPtr<Debugger> debugger) {
    _debugger = debugger;
    return *this;
}

AutoPtr<Debugger> Fun::getDebugger() {
    return _debugger;
}

}
