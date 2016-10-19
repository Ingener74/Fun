#include "Fun.h"

namespace fun {

using namespace std;
using namespace Poco;

Fun::Fun() {
}

Fun::~Fun() {
}

AutoPtr<Pot> Fun::parse(const string& source) {
    stringstream ss;
    ss << source;
    return parse(ss);
}

AutoPtr<Pot> Fun::parse(const istream& source) {
    AutoPtr<Pot> pot;
    Lexer lexer("", &source);
    Parser parser(lexer, pot);
    parser.set_debug_level(0);
    if (parser.parse())
        cerr << "Warning: parser.parse() not 0" << endl;
    return pot;
}

void Fun::eval(const string& script) {
    auto pot = parse(script);
    eval(pot);
}

void Fun::eval(const std::istream& script) {
    auto pot = parse(script);
    eval(pot);
}

void Fun::eval(const AutoPtr<Pot>& pot) {
}

Fun& Fun::setDebugger(Debugger debugger) {
    return *this;
}

//AutoPtr<Debugger> Fun::getDebugger() {
//    return _debugger;
//}

}
