#include "AstNodes/StatementNode.h"
#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Scope.h"

namespace fun {

Scope::Scope(StatementNode* statement) {
}

Scope::~Scope() {
}

void Scope::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

void Scope::addStatement(StatementNode* statement) {
    m_nodes.push_back(statement);
}

}
