#include <AstNodes/ArgumentList.h>
#include <AstNodes/Expression.h>
#include <iostream>

#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Scope.h"
#include "AstNodes/Function.h"

namespace fun {

using namespace std;

Function::Function(const std::string& id, ArgumentList* args, Scope* statements) :
    m_id(id), m_arguments(args), m_scope(statements) {
}

Function::~Function() {
}

void Function::accept(AstVisitor* visitor) {
    visitor->visit(this);
    m_arguments->accept(visitor);
    m_scope->accept(visitor);
}

}
