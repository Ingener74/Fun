#pragma once

#include "AstNode.h"

namespace fun {

class StatementNode;
class AstVisitor;

class Scope: public AstNode {
public:
    Scope(StatementNode* = nullptr);
    virtual ~Scope();

    void accept(AstVisitor*);

    void addStatement(StatementNode*);
};

}
