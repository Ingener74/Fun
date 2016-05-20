#pragma once

#include <AstNodes/Expr.h>

class AstVisitor;

namespace fun {

class Args;
class ExprList;

class Call: public Expr {
public:
    Call(const std::string& id, ExprList*);
    virtual ~Call();

    void accept(AstVisitor*);
};

}
