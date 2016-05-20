#pragma once

#include <string>
#include <AstNodes/Declaration.h>
//#include <AstNodes/Expression.h>

namespace fun {

class Id: public Declaration/*, public Expression*/ {
public:
    Id(const std::string& id);
    virtual ~Id();

    virtual void accept(AstVisitor*);

    std::string m_id;
};

}
