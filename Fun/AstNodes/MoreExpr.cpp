
#include "AstVisitors/AstVisitor.h"
#include "AstNodes/MoreExpr.h"

namespace fun {

MoreExpr::MoreExpr(Expr* arg1, Expr* arg2) {
    m_nodes.push_back(arg1);
    m_nodes.push_back(arg2);
}

MoreExpr::~MoreExpr() {
}

void MoreExpr::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

}
