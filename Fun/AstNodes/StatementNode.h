#pragma once

#include "AstNode.h"

namespace fun {

class AstVisitor;

class StatementNode: public AstNode {
public:
    StatementNode();
    virtual ~StatementNode();

    void accept(AstVisitor*);
};

}
