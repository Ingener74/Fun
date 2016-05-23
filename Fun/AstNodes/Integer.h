#pragma once

#include <AstNodes/Terminal.h>

namespace fun {

class AstVisitor;

class Integer: public Terminal {
public:
    Integer(long long);
    virtual ~Integer();

    virtual void accept(AstVisitor*);

    virtual Type getType() const {
        return Terminal::Integer;
    }

    long long m_integer;
};

}
