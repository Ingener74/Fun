#include <AstNodes/Plus.h>
#include <Fun1Ast.h>
#include <sstream>


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

void Plus::visit(Fun1Ast* ast) {
}

int Plus::getResult() {
    return m_lhs->getResult() + m_rhs->getResult();
}
