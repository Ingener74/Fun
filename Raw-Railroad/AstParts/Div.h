#pragma once

#include <string>

#include "Expr.h"

class Div: public Expr {
public:
    Div(Expr* lhs, Expr* rhs);
    virtual ~Div();

    virtual std::string toString() const ;

    virtual int getResult();

private:
    Expr* m_lhs, *m_rhs;
};
