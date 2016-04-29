#include <AstNodes/AssignExpr.h>
#include <Fun1Ast.h>
#include <iostream>
#include <sstream>


using namespace std;

AssignExpr::AssignExpr(const std::string& id, Expr* value) :
    m_id(id), m_value(value) {
}

AssignExpr::~AssignExpr() {
}

std::string AssignExpr::toString() const {
    stringstream ss;
    ss << m_id << " = " << m_value->getResult();
    return ss.str();
}

void AssignExpr::visit(Fun1Ast* ast) {
    ast->addVariable(m_id, m_value->getResult());
}
