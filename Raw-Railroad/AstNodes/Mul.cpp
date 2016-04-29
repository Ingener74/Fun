#include <AstNodes/Mul.h>
#include <iostream>
#include <sstream>


using namespace std;

Mul::Mul(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), m_rhs(rhs) {
}

Mul::~Mul() {
}

std::string Mul::toString() const {
    stringstream ss;
    ss << m_lhs->getResult() << " * " << m_rhs->getResult();
    return ss.str();
}

int Mul::getResult() {
    return m_lhs->getResult() * m_rhs->getResult();
}
