#pragma once

#include <AstNodes/Expr.h>

namespace fun {

class AstVisitor;

class MoreExpr: public Expr {
public:
    MoreExpr(Expr*, Expr*);
    virtual ~MoreExpr();

    void accept(AstVisitor*);
};

}
