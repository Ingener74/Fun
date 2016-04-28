#pragma once

#include <string>
#include "Expr.h"

class IdExpr: public Expr {
public:
    IdExpr(const std::string& id);
    virtual ~IdExpr();

    virtual std::string toString() const ;
private:
    std::string m_id;
};
