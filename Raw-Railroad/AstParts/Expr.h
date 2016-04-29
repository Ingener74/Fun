#pragma once

#include <string>

class Fun1Ast;

class Expr {
public:
    Expr();
    virtual ~Expr();

    virtual std::string toString() const {
        return "";
    }

    virtual void visit(Fun1Ast*) {
    }

    virtual int getResult(){
        return 0;
    }
};
