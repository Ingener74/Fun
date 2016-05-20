#pragma once

#include <string>
#include <vector>
#include <AstNodes/AstNode.h>

namespace fun {

class AstVisitor;

class ArgumentList: public AstNode {
public:
    ArgumentList(const std::string& arg = {});
    virtual ~ArgumentList();

    void accept(AstVisitor*);

    void addArg(const std::string& arg);

    std::vector<std::string> m_args;
};

}
