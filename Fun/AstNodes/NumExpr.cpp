#include <iostream>
#include <sstream>

#include "AstVisitors/AstVisitor.h"
#include "AstNodes/NumExpr.h"

namespace fun {

using namespace std;

NumExpr::NumExpr(int num) :
    m_num(num) {
}

NumExpr::~NumExpr() {
}

std::string NumExpr::toString() const {
    stringstream ss;
    ss << m_num;
    return ss.str();
}

void NumExpr::visit(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

int NumExpr::getResult() {
    return m_num;
}

}
