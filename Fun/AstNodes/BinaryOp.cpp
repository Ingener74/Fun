#include "AstVisitors/AstVisitor.h"
#include "AstNodes/BinaryOp.h"

namespace fun {

BinaryOp::BinaryOp(Op op, Expression* lhs, Expression* rhs) :
    m_operation(op), m_lhs(lhs), m_rhs(rhs) {
}

BinaryOp::~BinaryOp() {
}

void BinaryOp::accept(AstVisitor* v) {
    v->visit(this);
    m_lhs->accept(v);
    m_rhs->accept(v);
}

}
