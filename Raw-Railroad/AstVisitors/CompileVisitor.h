#pragma once

#include "AstVisitor.h"

namespace fun1 {

class CompileVisitor: public AstVisitor {
public:
    CompileVisitor();
    virtual ~CompileVisitor();
};

}
