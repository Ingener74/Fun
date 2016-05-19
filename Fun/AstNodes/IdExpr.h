#pragma once

#include <string>
#include "AstNodes/Expr.h"

namespace fun {

class IdExpression: public Expr {
public:
    IdExpression(const std::string& id);
    virtual ~IdExpression();

    virtual std::string toString() const;
private:
    std::string m_id;
};

}
