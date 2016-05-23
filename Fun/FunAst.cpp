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
        FunLexer myLexer(&input);
        myparser::parser prsr(myLexer, this);

        if (debug)
            prsr.set_debug_level(1);
        prsr.parse();
    } catch (const exception& e) {
        cerr << "error: " << e.what() << endl;
    }
}

void FunAst::setRoot(Scope* scope) {
    if (!m_scope) {
        m_scope = scope;
        if (m_resultVisitor)
            m_scope->setResultAstVisitor(m_resultVisitor);
    }
}

Scope* FunAst::getRoot() {
    return m_scope;
}

}
