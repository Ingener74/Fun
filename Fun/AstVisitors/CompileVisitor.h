#pragma once

#include "AstVisitors/AstVisitor.h"

namespace fun {

class CompileVisitor: public AstVisitor {
public:
    CompileVisitor();
    virtual ~CompileVisitor();
};

}
