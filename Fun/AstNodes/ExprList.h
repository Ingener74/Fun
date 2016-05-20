#pragma once

#include <AstNodes/AstNode.h>

namespace fun {

class Expr;
class AstVisitor;

class ExprList: public AstNode {
public:
    ExprList(Expr* = nullptr);
    virtual ~ExprList();

    void addExpression(Expr*);

    void accept(AstVisitor*);
};

}
