#pragma once

#include <AstNodes/Statement.h>

namespace fun {

class Id;
class AstVisitor;
class Scope;

class Function: public Statement {
public:
    Function(Id*, Id* = nullptr, Scope* = nullptr);
    virtual ~Function();

    virtual void accept(AstVisitor*);

    Id* m_id;
    Id* m_args;
    Scope* m_scope;
};

}
