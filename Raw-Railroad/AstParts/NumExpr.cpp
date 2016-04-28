#include <iostream>
#include <sstream>
#include "NumExpr.h"

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

void NumExpr::visit(MyAst* ast) {
}

int NumExpr::getResult() {
    return m_num;
}
