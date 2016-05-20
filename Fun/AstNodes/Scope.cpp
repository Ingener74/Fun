#include <AstNodes/Statement.h>
#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Scope.h"

namespace fun {

Scope::Scope(Statement* statement) {
}

Scope::~Scope() {
    if (m_resultAstVisitor)
        accept(m_resultAstVisitor);
}

void Scope::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_statements)
        n->accept(visitor);
}

void Scope::addStatement(Statement* statement) {
    m_statements.push_back(statement);
}

}
