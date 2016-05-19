#pragma once

#include <string>
#include "AstNodes/Expr.h"

namespace fun {

class Div: public Expr {
public:
    Div(Expr* lhs, Expr* rhs);
    virtual ~Div();

    virtual std::string toString() const;

    virtual int getResult();

private:
    Expr* m_lhs, *m_rhs;
};

}
