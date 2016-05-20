#include <iostream>

#include "AstVisitors/AstVisitor.h"
#include "AstNodes/ArgumentList.h"
#include "AstNodes/Id.h"
#include "AstNodes/Expression.h"
#include "AstNodes/Scope.h"
#include "AstNodes/Function.h"

namespace fun {

using namespace std;

Function::Function(Id* id, ArgumentList* args, Scope* statements) :
    m_id(id), m_arguments(args), m_scope(statements) {
}

Function::~Function() {
}

void Function::accept(AstVisitor* v) {
    v->visit(this);
    m_id->accept(v);
    m_arguments->accept(v);
    m_scope->accept(v);
}

}
