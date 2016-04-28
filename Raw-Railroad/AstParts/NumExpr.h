#pragma once

#include "Expr.h"

class NumExpr: public Expr {
public:
    NumExpr(int);
    virtual ~NumExpr();

    virtual std::string toString() const;

    virtual void visit(MyAst*);

    virtual int getResult();

private:
    int m_num;
};
