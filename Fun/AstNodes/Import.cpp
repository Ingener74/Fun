#include <iostream>

#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Import.h"

namespace fun {

using namespace std;

Import::Import(const string& library) :
    m_import(library) {
}

Import::~Import() {
}

void Import::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

}
