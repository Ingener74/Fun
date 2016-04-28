#include <sstream>

#include "MyAst.h"
#include "Minus.h"

using namespace std;

Minus::Minus(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), m_rhs(rhs) {
    cout << __PRETTY_FUNCTION__ << " " << m_lhs->getResult() << " - " << m_rhs->getResult() << endl;
}

Minus::~Minus() {
}

std::string Minus::toString() const {
    stringstream ss;
    ss << m_lhs->toString() << " - " << m_rhs->toString();
    cout << __PRETTY_FUNCTION__ << " " << ss.str() << endl;
    return ss.str();
}

int Minus::getResult() {
    return m_lhs->getResult() - m_rhs->getResult();
}
