#pragma once

#include "AstNodes/Expr.h"

namespace fun {

class AstVisitor;

class NumExpr: public Expr {
public:
    NumExpr(int);
    virtual ~NumExpr();

    virtual std::string toString() const;

    virtual void visit(AstVisitor*);

    virtual int getResult();

private:
    int m_num;
};

}
