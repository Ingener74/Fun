#pragma once

#include <vector>

namespace fun {

class VirtualMachine {
public:
    VirtualMachine();
    virtual ~VirtualMachine();

    void run(const std::vector<unsigned char>& program);
};

}
