#pragma once

#include <AstNodes/Statement.h>

namespace fun {

class Expression;

class Print: public Statement {
public:
    Print(Expression*);
    virtual ~Print();

    virtual void accept(AstVisitor*);

    Expression* m_expr;
};

}
