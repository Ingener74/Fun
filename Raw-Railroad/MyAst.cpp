#include <assert.h>

#include <MyParser.hpp>
#include "MyLexer.h"
#include "MyAst.h"

using namespace std;

MyAst::MyAst() {
}

MyAst::~MyAst() {
}

void MyAst::parse(std::istream& input) {
    try {
        MyLexer myLexer(&input);
        myparser::parser prsr(myLexer, this);
        prsr.parse();
    } catch (const std::exception& e) {
        cerr << "error: " << e.what() << endl;
    }
}

void MyAst::importLibrary(Import* import) {
    cout << __PRETTY_FUNCTION__ << " " << import->getImport() << endl;
}

void MyAst::functionDefinition(FuncType* func) {
    cout << __PRETTY_FUNCTION__ << endl;
}

void MyAst::printId(Print* print) {
    printVariable(print->getId());
}

void MyAst::expressionDefinition(Expr* func) {
    cout << __PRETTY_FUNCTION__ << endl;
}

void MyAst::addVariable(const std::string& id, int value) {
    auto erased = m_variables.erase(id);
    auto res = m_variables.insert(make_pair(id, value));
    assert(res.second);
}

void MyAst::printVariable(const std::string& id) {
    cout << m_variables[id] << endl;
}

