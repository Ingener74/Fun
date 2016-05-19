#include "FunAst.h"

#include <assert.h>
#include <FunParser.hpp>

#include "FunLexer.h"

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

void FunAst::pushScope(Scope* scope) {
    m_scope = scope;
}

Scope* FunAst::getScope() {
    return m_scope;
}

void FunAst::importLibrary(Import* import) {
}

void FunAst::functionDefinition(Function* func) {
}

void FunAst::printId(Print* print) {
    printVariable(print->getId());
}

void FunAst::expressionDefinition(Expr* func) {
}

void FunAst::addVariable(const string& id, int value) {
    auto erased = m_variables.erase(id);
    auto res = m_variables.insert(make_pair(id, value));
    assert(res.second);
}

void FunAst::printVariable(const string& id) {
    cout << m_variables[id] << endl;
}

}
