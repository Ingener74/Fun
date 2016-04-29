#pragma once

#include <AstNodes/Expr.h>

class NumExpr: public Expr {
public:
    NumExpr(int);
    virtual ~NumExpr();

    virtual std::string toString() const;

    virtual void visit(Fun1Ast*);

    virtual int getResult();

private:
    int m_num;
};
