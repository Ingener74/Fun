#pragma once

#include <AstNodes/Expression.h>

namespace fun {

class AstVisitor;

class Integer: public Expression {
public:
    Integer(int);
    virtual ~Integer();

    virtual void accept(AstVisitor*);

    int m_num;
};

}
