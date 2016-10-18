#include "test.h"
#include "Utils.h"

using namespace std;
using namespace fun;
using namespace Poco;

Result parse(const string& source) {
    Result r;
    r.d = new DebuggerMock;
    r.v = new Interpreter(r.d);
    r.pot = new Pot;
    stringstream ss;
    ss << source;
    Lexer lexer("", &ss);
    Parser parser(lexer, r.pot);
    parser.set_debug_level(0);
    if (parser.parse())
        cerr << "Warning: parser.parse() not 0" << endl;
    return r;
}

