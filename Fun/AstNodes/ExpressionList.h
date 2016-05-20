#pragma once

#include <vector>
#include <AstNodes/AstNode.h>

namespace fun {

class Expression;
class AstVisitor;

class ExpressionList: public AstNode {
public:
    ExpressionList(Expression* = nullptr);
    virtual ~ExpressionList();

    void addExpression(Expression*);

    void accept(AstVisitor*);

    std::vector<Expression*> m_expressions;
};

}
