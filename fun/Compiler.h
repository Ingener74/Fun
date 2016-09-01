#pragma once

#include <Declarations.h>
#include <Visitor.h>

namespace fun {

class Compiler: public Visitor {
public:
    Compiler();
    virtual ~Compiler();

    const Program& getProgram() const;

private:
    Program _program;
};

}
