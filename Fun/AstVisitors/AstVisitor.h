#pragma once

namespace fun {

class AstVisitor {
public:
    AstVisitor();
    virtual ~AstVisitor();

    void visit(class AstNode*);
};

}
