#pragma once

#include "Utils.h"

namespace fun1 {

class AstNode {
public:
    AstNode();
    virtual ~AstNode();

    void accept(class AstVisitor*);

    template<typename T, typename ... Args>
    void createNode(Args&& ... args) {
        m_nodes.push_back(make_unique_<T>(std::forward<Args>(args)...));
    }

protected:
    std::list<std::unique_ptr<AstNode>> m_nodes;
};

}
