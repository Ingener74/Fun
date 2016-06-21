#pragma once

#include <Visitor.h>

namespace fun {

class Interpreter: public Visitor {
public:
    Interpreter();
    virtual ~Interpreter();
};

}
