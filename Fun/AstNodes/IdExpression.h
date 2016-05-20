#pragma once

#include <AstNodes/Expression.h>
#include <string>

namespace fun {

class IdExpression: public Expression {
public:
    IdExpression(const std::string& id);
    virtual ~IdExpression();

    virtual void accept(AstVisitor*);

    std::string m_id;
};

}
