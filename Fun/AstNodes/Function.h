#pragma once

#include <string>
#include <AstNodes/StatementNode.h>

namespace fun {

class Args;
class AstVisitor;
class FunctionStatements;

class Function: public StatementNode {
public:
    Function(const std::string& id, Args*, FunctionStatements*);
    virtual ~Function() = default;

    void accept(AstVisitor*);
};

}
