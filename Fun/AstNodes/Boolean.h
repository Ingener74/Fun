#pragma once

#include <AstNodes/Terminal.h>

namespace fun {

class AstVisitor;

class Boolean: public Terminal {
public:
    Boolean(bool value);
    virtual ~Boolean();

    virtual void accept(AstVisitor*);

    virtual Type getType() const {
        return Terminal::Boolean;
    }

    bool m_value;
};

}
