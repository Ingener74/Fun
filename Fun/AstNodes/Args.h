#pragma once

#include <string>
#include <vector>
#include <AstNodes/AstNode.h>

namespace fun {

class AstVisitor;

class Args: public AstNode {
public:
    Args(const std::string& arg = {});
    virtual ~Args();

    void accept(AstVisitor*);

    void addArg(const std::string& arg);

    const std::string& getArg(size_t index) const;
    const std::vector<std::string>& getArgs() const;

private:
    std::vector<std::string> m_args;
};

}
