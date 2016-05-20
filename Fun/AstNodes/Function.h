#pragma once

#include <string>
#include <AstNodes/StatementNode.h>

namespace fun {

class Args;
class AstVisitor;
class Scope;

class Function: public StatementNode {
public:
    Function(const std::string& id, Args*, Scope*);
    virtual ~Function();

    void accept(AstVisitor*);
};

}
