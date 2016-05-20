#pragma once

namespace fun {

class AstVisitor;

class AstNode {
public:
    AstNode() = default;
    virtual ~AstNode() = default;

    virtual void accept(AstVisitor*) = 0;
};

}
