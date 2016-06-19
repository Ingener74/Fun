#pragma once

#include <Visitor.h>

namespace fun {

class CompileVisitor: public Visitor {
public:
    CompileVisitor();
    virtual ~CompileVisitor();
};

}
