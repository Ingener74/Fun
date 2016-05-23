#pragma once

#include <AstNodes/Expression.h>

namespace fun {

class AstVisitor;

class Integer: public Expression {
public:
    Integer(long long);
    virtual ~Integer();

    virtual void accept(AstVisitor*);

    long long m_integer;
};

}
