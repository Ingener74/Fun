#pragma once

#include <string>
#include <AstNodes/StatementNode.h>

namespace fun {

class Print: public StatementNode {
public:
    Print(const std::string& id);
    virtual ~Print();

    const std::string& getId() const {
        return m_id;
    }

    void accept(AstVisitor*);

private:
    std::string m_id;
};

}
