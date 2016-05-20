#pragma once

#include <AstNodes/Expression.h>

namespace fun {

class Id;
class ExpressionList;
class AstVisitor;

class Call: public Expression {
public:
    Call(Id*, ExpressionList*);
    virtual ~Call();

    virtual void accept(AstVisitor*);

    Id* m_id = nullptr;
    ExpressionList* m_expressionList = nullptr;
};

}
