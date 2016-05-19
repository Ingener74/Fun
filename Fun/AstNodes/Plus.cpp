#include "AstNodes/Plus.h"

#include <sstream>

#include "FunAst.h"

namespace fun {

using namespace std;

Plus::Plus(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), m_rhs(rhs) {
}

Plus::~Plus() {
}

std::string Plus::toString() const {
    stringstream ss;
    ss << m_lhs->toString() << " + " << m_rhs->toString();
    return ss.str();
}

void Plus::visit(FunAst* ast) {
}

int Plus::getResult() {
    return m_lhs->getResult() + m_rhs->getResult();
}

}
