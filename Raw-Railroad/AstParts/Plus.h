#pragma once

#include <string>

#include "Expr.h"

class MyAst;

class Plus: public Expr {
public:
    Plus(Expr*, Expr*);
    virtual ~Plus();

    virtual std::string toString() const ;

    virtual void visit(MyAst*);

    virtual int getResult();

private:
    Expr* m_lhs, *m_rhs;
};
