#pragma once

#include <vector>

#include <Visitor.h>

namespace fun {

using Program = std::vector<unsigned char>;

class Compiler: public Visitor {
public:
    Compiler();
    virtual ~Compiler();

    const Program& getProgram() const;

private:
    Program _program;
};

}
