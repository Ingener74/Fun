
#include "AstNodes/Expr.h"
#include "AstNodes/Scope.h"
#include "AstVisitors/AstVisitor.h"
#include "AstNodes/IfStatement.h"

namespace fun {

IfStatement::IfStatement(Expr* condition, Scope* then_scope, Scope* else_scope) {
    m_nodes.push_back(condition);
    m_nodes.push_back(then_scope);
    if(else_scope)
        m_nodes.push_back(else_scope);
}

IfStatement::~IfStatement() {
}

void IfStatement::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

}
