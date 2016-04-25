#pragma once

#include <string>

class Expr {
public:
    Expr();
    virtual ~Expr();

    virtual std::string toString() const { return ""; }
};
