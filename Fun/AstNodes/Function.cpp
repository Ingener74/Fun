#include <iostream>

#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Id.h"
#include "AstNodes/Expression.h"
#include "AstNodes/Scope.h"
#include "AstNodes/Function.h"

namespace fun {

using namespace std;

Function::Function(Id* id, Id* args, Scope* statements) :
        m_id(id), m_args(args), m_scope(statements) {
}

Function::~Function() {
}

void Function::accept(AstVisitor* v) {
    m_id->accept(v);
    if (m_args)
        m_args->accept(v);
    if (m_scope)
        m_scope->accept(v);
    v->visit(this);
}

}
