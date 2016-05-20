#pragma once

#include <AstNodes/Statement.h>

namespace fun {

using namespace std;

class Id;
class AstVisitor;

class Import: public Statement {
public:
    Import(Id*);
    virtual ~Import();

    virtual void accept(AstVisitor*);

    Id* m_import;
};

}
