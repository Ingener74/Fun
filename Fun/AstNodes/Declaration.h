#pragma once

#include <AstNodes/AstNode.h>

namespace fun {

class Declaration: public AstNode {
public:
    Declaration();
    virtual ~Declaration();
};

}
