#pragma once

#include <string>
#include <AstNodes/Expression.h>

class AstVisitor;

namespace fun {

class ArgumentList;
class ExpressionList;

class Call: public Expression {
public:
    Call(const std::string& id, ExpressionList*);
    virtual ~Call();

    virtual void accept(AstVisitor*);

    std::string m_id;
    ExpressionList* m_expressionList = nullptr;
};

}
