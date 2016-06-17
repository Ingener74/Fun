#pragma once

#include <string>

#include <AstNodes/Terminal.h>

namespace fun {

class AstVisitor;

class String: public Terminal {
public:
    String(const std::string& value);
    virtual ~String();

    virtual void accept(AstVisitor*);

    virtual Type getType() const {
        return Terminal::String;
    }

    std::string m_value;
};

}
