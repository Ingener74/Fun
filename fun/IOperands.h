#pragma once

namespace fun {

class Terminal;

class IOperands {
public:
    virtual ~IOperands() = default;

    virtual const std::vector<Terminal*>& getOperands() const = 0;
};

}
