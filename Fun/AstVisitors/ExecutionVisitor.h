#pragma once

#include "AstVisitors/AstVisitor.h"

namespace fun {

class ExecutionVisitor: public AstVisitor {
public:
    ExecutionVisitor();
    virtual ~ExecutionVisitor();
};

}
