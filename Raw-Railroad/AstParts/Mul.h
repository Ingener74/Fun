#pragma once

#include <string>
#include "Expr.h"

class Mul: public Expr {
public:
    Mul(Expr* lhs, Expr* rhs);
    virtual ~Mul();

    virtual std::string toString() const ;

    virtual int getResult();

private:
    Expr* m_lhs, *m_rhs;
};
