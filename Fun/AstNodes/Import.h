#pragma once

#include <string>
#include <AstNodes/StatementNode.h>

namespace fun {

using namespace std;

class AstVisitor;

class Import: public StatementNode {
public:
    Import(const std::string& library);
    virtual ~Import();

    void accept(AstVisitor*);

    const std::string& getImport() const {
        return m_import;
    }

private:
    std::string m_import;
};

}
