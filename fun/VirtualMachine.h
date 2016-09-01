#pragma once

#include <Declarations.h>

namespace fun {

class VirtualMachine {
public:
    VirtualMachine();
    virtual ~VirtualMachine();

    void run(const Program& program);
};

}
