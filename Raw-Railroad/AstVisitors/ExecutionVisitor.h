#pragma once

#include <AstVisitors/AstVisitor.h>

namespace fun1 {

class ExecutionVisitor: public AstVisitor {
public:
    ExecutionVisitor();
    virtual ~ExecutionVisitor();
};

}
