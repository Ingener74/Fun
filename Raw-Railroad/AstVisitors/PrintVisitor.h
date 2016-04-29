#pragma once

#include "AstVisitor.h"

namespace fun1 {

class PrintVisitor: public AstVisitor {
public:
    PrintVisitor();
    virtual ~PrintVisitor();
};

}
