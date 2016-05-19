#pragma once

#include "AstVisitors/AstVisitor.h"

namespace fun {

class PrintVisitor: public AstVisitor {
public:
    PrintVisitor();
    virtual ~PrintVisitor();

    void visit(class Import*);
    void visit(class AssignExpr*);
};

}
