#pragma once

namespace fun {

class Terminal;

class IOperands {
public:
    virtual ~IOperands() = default;

    const std::vector<Terminal*>& getOperands() const;
};

}
