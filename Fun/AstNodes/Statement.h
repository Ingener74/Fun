#pragma once

#include "AstNode.h"

namespace fun {

class AstVisitor;

class Statement: public AstNode {
public:
    Statement();
    virtual ~Statement();
};

}
