#pragma once

#include <Visitor.h>

namespace fun {

class Compiler: public Visitor {
public:
    Compiler();
    virtual ~Compiler();
};

}
