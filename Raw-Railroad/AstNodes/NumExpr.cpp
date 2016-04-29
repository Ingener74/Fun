#include <AstNodes/NumExpr.h>
#include <iostream>
#include <sstream>

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

void NumExpr::visit(Fun1Ast* ast) {
}

int NumExpr::getResult() {
    return m_num;
}
