#pragma once

#include <AstNodes/Expression.h>

namespace fun {

class Real: public Expression {
public:
    Real(double);
    virtual ~Real();

    virtual void accept(AstVisitor*);

    double m_real;
};

}
