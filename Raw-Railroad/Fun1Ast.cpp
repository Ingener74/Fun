#include <assert.h>
#include <Fun1Ast.h>

#include <MyParser.hpp>
#include "MyLexer.h"

using namespace std;

Fun1Ast::Fun1Ast() {
}

Fun1Ast::~Fun1Ast() {
}

void Fun1Ast::parse(std::istream& input, bool debug) {
    try {
        MyLexer myLexer(&input);
        myparser::parser prsr(myLexer, this);
        if(debug)
            prsr.set_debug_level(1);
        prsr.parse();
    } catch (const std::exception& e) {
        cerr << "error: " << e.what() << endl;
    }
}

void Fun1Ast::compile() {
}

void Fun1Ast::run() {
}

void Fun1Ast::importLibrary(Import* import) {
	cout << import->getImport() << endl;
}

void Fun1Ast::functionDefinition(Function* func) {
}

void Fun1Ast::printId(Print* print) {
    printVariable(print->getId());
}

void Fun1Ast::expressionDefinition(Expr* func) {
}

void Fun1Ast::addVariable(const std::string& id, int value) {
    auto erased = m_variables.erase(id);
    auto res = m_variables.insert(make_pair(id, value));
    assert(res.second);
}

void Fun1Ast::printVariable(const std::string& id) {
    cout << m_variables[id] << endl;
}

