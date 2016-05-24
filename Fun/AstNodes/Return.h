#pragma once

#include <AstNodes/Statement.h>

namespace fun {

class Expression;
class AstVisitor;

class Return: public Statement {
public:
    Return(Expression* = nullptr);
    virtual ~Return();

    virtual void accept(AstVisitor*);

    Expression* m_expr;
};

}
