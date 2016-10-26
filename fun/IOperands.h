#pragma once

namespace fun {

class Terminal;

class IOperands {
public:
    virtual ~IOperands() = default;

    virtual const std::vector<Poco::AutoPtr<Terminal>>& getOperands() const = 0;
    virtual std::vector<Poco::AutoPtr<Terminal>>& getOperands() = 0;
};

}
