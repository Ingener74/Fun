#pragma once

#include <AstNodes/Expression.h>

namespace fun {

class Terminal: public Expression {
public:
    enum Type {
        Integer, Real, String, Boolean, Class, Function, Unknown,
    };

    Terminal();
    virtual ~Terminal();

    virtual Type getType() const {
        return Unknown;
    }
};

}
