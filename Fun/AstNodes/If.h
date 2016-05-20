#pragma once

#include <AstNodes/Statement.h>

namespace fun {

class Expression;
class Scope;
class AstVisitor;

class If: public Statement {
public:
    If(Expression* condition, Scope* then_scope, Scope* else_scope = nullptr);
    virtual ~If();

    void accept(AstVisitor*);

    Expression* m_condition = nullptr;
    Scope* m_thenScope = nullptr, * m_elseScope = nullptr;
};

}
