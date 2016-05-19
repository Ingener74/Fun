#include <iostream>
#include <sstream>

#include "AstVisitors/AstVisitor.h"
#include "AstNodes/AssignExpr.h"

namespace fun {

using namespace std;

AssignExpr::AssignExpr(const std::string& id, Expr* value) :
    m_id(id), m_value(value) {
}

AssignExpr::~AssignExpr() {
}

std::string AssignExpr::toString() const {
    stringstream ss;
    ss << m_id << " = " << m_value->getResult();
    return ss.str();
}

void AssignExpr::visit(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

}
