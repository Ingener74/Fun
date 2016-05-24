#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Expression.h"
#include "AstNodes/Return.h"

namespace fun {

Return::Return(Expression* expr) :
        m_expr(expr) {
}

Return::~Return() {
}

void Return::accept(AstVisitor* v) {
    if (m_expr)
        m_expr->accept(v);
    v->visit(this);
}

}
