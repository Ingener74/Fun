#pragma once

#include <AstNodes/Statement.h>
#include <string>

namespace fun {

using namespace std;

class AstVisitor;

class Import: public Statement {
public:
    Import(const std::string& library);
    virtual ~Import();

    virtual void accept(AstVisitor*);

    std::string m_import;
};

}
