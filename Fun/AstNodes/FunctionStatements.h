#pragma once

#include <vector>

namespace fun {

class Expr;

class FunctionStatements {
public:
    FunctionStatements(Expr* = nullptr);
    virtual ~FunctionStatements();

    void addExpression(Expr*);

    const std::vector<Expr*>& getExpressions() const;

private:
    std::vector<Expr*> m_expressions;
};

}
