#include "AstNodes/Expression.h"
#include <AstNodes/ExpressionList.h>
#include "AstVisitors/AstVisitor.h"

namespace fun {

ExpressionList::ExpressionList(Expression* expr) {
    if (expr)
        m_expressions.push_back(expr);
}

ExpressionList::~ExpressionList() {
}

void ExpressionList::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto n : m_expressions)
        n->accept(visitor);
}

void ExpressionList::addExpression(Expression* expr) {
    if (expr)
        m_expressions.push_back(expr);
}

}
