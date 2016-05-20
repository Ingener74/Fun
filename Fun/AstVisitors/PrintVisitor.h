#pragma once

#include "AstVisitors/AstVisitor.h"

namespace fun {

class Import;
class Assign;

class PrintVisitor: public AstVisitor {
public:
    PrintVisitor();
    virtual ~PrintVisitor();

    virtual void visit(class Import*);
    virtual void visit(class Assign*);
    virtual void visit(class Print*);
};

}
