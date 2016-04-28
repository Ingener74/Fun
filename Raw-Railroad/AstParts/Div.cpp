
#include <iostream>
#include <sstream>

#include "Div.h"

using namespace std;

Div::Div(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), m_rhs(rhs) {
}

Div::~Div() {
}

std::string Div::toString() const {
    stringstream ss;
    ss << m_lhs->getResult() << " / " << m_rhs->getResult();
    return ss.str();
}

int Div::getResult() {
    return m_lhs->getResult() / m_rhs->getResult();
}
