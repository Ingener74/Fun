
#include <iostream>
#include <sstream>

#include "Div.h"

using namespace std;

Div::Div(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), m_rhs(rhs) {
    cout << __PRETTY_FUNCTION__ << " " << m_lhs->getResult() << " / " << m_rhs->getResult() << endl;
}

Div::~Div() {
}

std::string Div::toString() const {
    stringstream ss;
    ss << m_lhs->getResult() << " / " << m_rhs->getResult();

    cout << __PRETTY_FUNCTION__ << " " << ss.str() << endl;

    return ss.str();
}

int Div::getResult() {
    return m_lhs->getResult() / m_rhs->getResult();
}
