#pragma once

#include <string>

#include "Expr.h"

class AssignExpr : public Expr {
public:
    AssignExpr(const std::string& id, int value);
    virtual ~AssignExpr();

    virtual std::string toString() const ;

private:
    std::string m_id;
    int m_value;
};