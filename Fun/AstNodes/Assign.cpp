#include <iostream>
#include <sstream>

#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Assign.h"

namespace fun {

using namespace std;

Assign::Assign(const std::string& id, Expression* value) :
    m_id(id), m_value(value) {
}

Assign::~Assign() {
}

void Assign::accept(AstVisitor* visitor) {
    visitor->visit(this);
    m_value->accept(visitor);
}

}
