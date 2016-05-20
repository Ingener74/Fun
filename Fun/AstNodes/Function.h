#pragma once

#include <AstNodes/Statement.h>
#include <string>

namespace fun {

class ArgumentList;
class AstVisitor;
class Scope;

class Function: public Statement {
public:
    Function(const std::string& id, ArgumentList*, Scope*);
    virtual ~Function();

    virtual void accept(AstVisitor*);

    std::string m_id;
    ArgumentList* m_arguments;
    Scope* m_scope;
};

}
