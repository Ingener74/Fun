#pragma once

#include <AstNodes/Statement.h>

namespace fun {

class Expression;
class Scope;
class AstVisitor;

class While: public Statement {
public:
    While(Expression*, Scope*);
    virtual ~While();

    virtual void accept(AstVisitor*);

    Expression* m_condition;
    Scope* m_scope;
};

}
