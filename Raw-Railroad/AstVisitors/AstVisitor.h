#pragma once

namespace fun1 {

class AstVisitor {
public:
    AstVisitor();
    virtual ~AstVisitor();

    void visit(class AstNode*);
};

}
