#include "AstNodes/Expression.h"
#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Print.h"

namespace fun {

Print::Print(Expression* expr) :
    m_expr(expr) {
}

Print::~Print() {
}

void Print::accept(AstVisitor* v) {
    v->visit(this);
    m_expr->accept(v);
}

}
