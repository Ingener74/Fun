#pragma once

#include "Declarations.h"

namespace fun {

class Terminal;

class IOperands {
public:
    virtual ~IOperands() = default;

    virtual size_t count() const = 0;

    virtual Type type(size_t operand) const = 0;

    virtual Poco::AutoPtr<Terminal> operand(size_t operand) const = 0;

    virtual bool boolean(size_t operand) const = 0;

    virtual long long int integer(size_t operand) const = 0;

    virtual double real(size_t operand) const = 0;

    virtual std::string str(size_t operand) const = 0;
};

}
