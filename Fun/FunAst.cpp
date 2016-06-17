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

        if (debug)
            parser.set_debug_level(1);
        parser.parse();

        if (m_resultVisitor && m_scope)
            m_scope->accept(m_resultVisitor);

    } catch (const exception& e) {
        cerr << "error: " << e.what() << endl;
    }
}

void FunAst::setRoot(Scope* scope) {
    if (!m_scope) {
        m_scope = scope;
//        if (m_resultVisitor)
//            m_scope->setResultAstVisitor(m_resultVisitor);
    }
}

Scope* FunAst::getRoot() {
    return m_scope;
}

}
