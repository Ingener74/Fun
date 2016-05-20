#pragma once

#include <AstNodes/Statement.h>

namespace fun {

class Expression: public Statement {
public:
    Expression();
    virtual ~Expression();
};

}
