#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Print.h"

namespace fun {

Print::Print(Expr* expr) :
    m_expr(expr) {
}

Print::~Print() {
}

void Print::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

}
