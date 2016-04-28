#pragma once

#include <string>

class MyAst;

class Expr {
public:
    Expr();
    virtual ~Expr();

    virtual std::string toString() const {
        return "";
    }

    virtual void visit(MyAst*) {
    }

    virtual int getResult(){
        return 0;
    }
};
