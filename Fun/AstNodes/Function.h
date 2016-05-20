#pragma once

#include <AstNodes/Statement.h>

namespace fun {

class ArgumentList;
class Id;
class AstVisitor;
class Scope;

class Function: public Statement {
public:
    Function(Id*, ArgumentList*, Scope*);
    virtual ~Function();

    virtual void accept(AstVisitor*);

    Id* m_id;
    ArgumentList* m_arguments;
    Scope* m_scope;
};

}
