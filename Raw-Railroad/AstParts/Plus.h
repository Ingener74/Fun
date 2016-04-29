#pragma once

#include <Expr.h>
#include <string>


class Fun1Ast;

class Plus: public Expr {
public:
    Plus(Expr*, Expr*);
    virtual ~Plus();

    virtual std::string toString() const ;

    virtual void visit(Fun1Ast*);

    virtual int getResult();

private:
    Expr* m_lhs, *m_rhs;
};
