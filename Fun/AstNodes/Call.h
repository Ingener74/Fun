#pragma once

#include <AstNodes/Expression.h>

namespace fun {

class Id;
class Expression;
class AstVisitor;

class Call: public Expression {
public:
    Call(Id*, Expression* = nullptr);
    virtual ~Call();

    virtual void accept(AstVisitor*);

    Id* m_id = nullptr;
    Expression* m_arg = nullptr;
};

}
