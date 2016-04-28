#pragma once

#include <string>

#include "Expr.h"

class MyAst;

class Minus: public Expr {
public:
    Minus(Expr*, Expr*);
    virtual ~Minus();

    virtual std::string toString() const ;

    virtual int getResult();

private:
    Expr* m_lhs, *m_rhs;
};
