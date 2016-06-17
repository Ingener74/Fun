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
    m_condition->accept(visitor);
    if (m_elseScope)
        m_elseScope->accept(visitor);
    if (m_thenScope)
        m_thenScope->accept(visitor);
    visitor->visit(this);
}

}
