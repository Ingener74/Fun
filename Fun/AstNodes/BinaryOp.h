#pragma once

#include <AstNodes/Expression.h>

namespace fun {

class BinaryOp: public Expression {
public:
    enum Op {
        ADD, ADD_ASSIGN,
        SUB, SUB_ASSIGN,
        MUL, MUL_ASSIGN,
        DIV, DIV_ASSIGN,
        MOD, MOD_ASSIGN,
        MORE, MORE_EQUAL,
        LESS, LESS_EQUAL,

    };

    BinaryOp(Op, Expression*, Expression*);
    virtual ~BinaryOp();

    virtual void accept(AstVisitor*);

    Op m_operation;
    Expression* m_lhs = nullptr, *m_rhs = nullptr;
};

}
