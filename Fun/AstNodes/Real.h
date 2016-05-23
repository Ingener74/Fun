#pragma once

#include <AstNodes/Terminal.h>

namespace fun {

class Real: public Terminal {
public:
    Real(double);
    virtual ~Real();

    virtual void accept(AstVisitor*);

    virtual Type getType() const {
        return Terminal::Real;
    }

    double m_real;
};

}
