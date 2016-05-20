#include <AstNodes/Expression.h>
#include <AstNodes/If.h>
#include "AstNodes/Scope.h"
#include "AstVisitors/AstVisitor.h"

namespace fun {

If::If(Expression* condition, Scope* then_scope, Scope* else_scope) :
    m_condition(condition), m_thenScope(then_scope), m_elseScope(else_scope) {
}

If::~If() {
}

void If::accept(AstVisitor* visitor) {
    visitor->visit(this);
    m_condition->accept(visitor);
    m_elseScope->accept(visitor);
    if (m_thenScope)
        m_thenScope->accept(visitor);
}

}
