#include "FunParser.hpp"
#include "FunLexer.h"
#include "FunAst.h"

namespace fun {

using namespace std;

FunAst::FunAst() {
}

FunAst::~FunAst() {
}

void FunAst::parse(istream& input, bool debug) {
    try {
        FunLexer lexer(&input);
        FunParser parser(lexer, this);
        parser.set_debug_level(debug);
        parser.parse();

    } catch (const exception& e) {
        cerr << "error: " << e.what() << endl;
    }
}

void FunAst::setRoot(Scope* scope) {
    if (!m_scope) {
        m_scope = scope;
    }
}

Scope* FunAst::getRoot() {
    return m_scope;
}

}
