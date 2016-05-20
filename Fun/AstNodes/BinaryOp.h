#pragma once

#include <AstNodes/Expression.h>

namespace fun {

class BinaryOp: public Expression {
public:
    enum Op {
        PLUS, MINUS, MULTIPLY, DIVIDE, MORE, LESS,
    };

    BinaryOp(Op, Expression*, Expression*);
    virtual ~BinaryOp();

    virtual void accept(AstVisitor*);

    Op m_operation;
    Expression* m_lhs = nullptr, *m_rhs = nullptr;
};

}
