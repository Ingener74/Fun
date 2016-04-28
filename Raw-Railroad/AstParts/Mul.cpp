#include <iostream>
#include <sstream>

#include "Mul.h"

using namespace std;

Mul::Mul(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), m_rhs(rhs) {
    cout << __PRETTY_FUNCTION__ << " " << m_lhs->getResult() << " * " << m_rhs->getResult() << endl;
}

Mul::~Mul() {
}

std::string Mul::toString() const {
    stringstream ss;
    ss << m_lhs->getResult() << " * " << m_rhs->getResult();
    cout << __PRETTY_FUNCTION__ << " " << ss.str() << endl;
    return ss.str();
}

int Mul::getResult() {
    return m_lhs->getResult() * m_rhs->getResult();
}
