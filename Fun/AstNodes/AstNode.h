#pragma once

#include <vector>
#include "Utils.h"

namespace fun {

class AstVisitor;

class AstNode {
public:
    AstNode();
    virtual ~AstNode();

    void accept(AstVisitor*);

    template<typename T, typename ... Args>
    void createNode(Args&& ... args) {
        m_nodes.push_back(make_unique_<T>(std::forward<Args>(args)...));
    }

protected:
    std::vector<AstNode*> m_nodes;
};

}
