#pragma once

#include <AstNodes/Expression.h>
#include <string>

namespace fun {

class AstVisitor;

class Assign : public Expression {
public:
    Assign(const std::string& id, Expression* value);
    virtual ~Assign();

    virtual void accept(AstVisitor*);

    std::string m_id;
    Expression* m_value;
};

}
