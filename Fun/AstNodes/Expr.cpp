#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Expr.h"

namespace fun {

Expr::Expr() {
}

Expr::~Expr() {
}

void Expr::visit(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

}
