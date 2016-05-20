#pragma once

#include <vector>
#include <AstNodes/AstNode.h>

namespace fun {

class Id;
class AstVisitor;

class ArgumentList: public AstNode {
public:
    ArgumentList(Id* = nullptr);
    virtual ~ArgumentList();

    void accept(AstVisitor*);

    void addArg(Id*);

    std::vector<Id*> m_args;
};

}
