#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Expression.h"
#include "AstNodes/Scope.h"
#include "AstNodes/While.h"

namespace fun {

While::While(Expression* condition, Scope* scope) :
        m_condition(condition), m_scope(scope) {
}

While::~While() {
}

void While::accept(AstVisitor* v) {
    v->visit(this);
    m_condition->accept(v);
    m_scope->accept(v);
}

}
