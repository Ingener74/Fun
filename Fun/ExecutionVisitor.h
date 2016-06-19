#pragma once

#include <Visitor.h>

namespace fun {

class ExecutionVisitor: public Visitor {
public:
    ExecutionVisitor();
    virtual ~ExecutionVisitor();
};

}
