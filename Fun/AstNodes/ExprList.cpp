#include "AstNodes/Expr.h"
#include "AstVisitors/AstVisitor.h"
#include "AstNodes/ExprList.h"

namespace fun {

ExprList::ExprList(Expr* expr) {
    if (expr)
        m_nodes.push_back(expr);
}

ExprList::~ExprList() {
}

void ExprList::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

void ExprList::addExpression(Expr* expr) {
    if (expr)
        m_nodes.push_back(expr);
}

}
