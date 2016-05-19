#pragma once

#include <string>
#include "AstNodes/Expr.h"

namespace fun {

class FunAst;

class Plus: public Expr {
public:
    Plus(Expr*, Expr*);
    virtual ~Plus();

    virtual std::string toString() const;

    virtual void visit(FunAst*);

    virtual int getResult();

private:
    Expr* m_lhs, *m_rhs;
};

}
