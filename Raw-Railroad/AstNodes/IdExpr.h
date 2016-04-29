#pragma once

#include <AstNodes/Expr.h>
#include <string>

class IdExpression: public Expr {
public:
    IdExpression(const std::string& id);
    virtual ~IdExpression();

    virtual std::string toString() const ;
private:
    std::string m_id;
};
