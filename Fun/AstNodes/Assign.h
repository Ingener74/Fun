#pragma once

#include <AstNodes/Expression.h>

namespace fun {

class Id;
class AstVisitor;

class Assign : public Expression {
public:
    Assign(Id* id, Expression* value);
    virtual ~Assign();

    virtual void accept(AstVisitor*);

    Id* m_id;
    Expression* m_value;
};

}
