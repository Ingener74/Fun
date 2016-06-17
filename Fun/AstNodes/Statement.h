#pragma once

#include <AstNodes/AstNode.h>

namespace fun {

class AstVisitor;

class Statement: public AstNode {
public:
    Statement();
    virtual ~Statement();
};

}
