#include "AstNodes/FunctionStatements.h"

namespace fun {

FunctionStatements::FunctionStatements(Expr* expr) {
    if (expr)
        addExpression(expr);
}

FunctionStatements::~FunctionStatements() {
}

void FunctionStatements::addExpression(Expr* expr) {
    m_expressions.push_back(expr);
}

const std::vector<Expr*>& FunctionStatements::getExpressions() const {
    return m_expressions;
}

}
