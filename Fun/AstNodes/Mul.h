#pragma once

#include <string>
#include "AstNodes/Expr.h"

namespace fun {

class Mul: public Expr {
public:
    Mul(Expr* lhs, Expr* rhs);
    virtual ~Mul();

    virtual std::string toString() const;

    virtual int getResult();

private:
    Expr* m_lhs, *m_rhs;
};

}
