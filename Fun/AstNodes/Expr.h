#pragma once

#include <string>
#include <AstNodes/StatementNode.h>

namespace fun {

class AstVisitor;

class Expr: public StatementNode {
public:
    Expr();
    virtual ~Expr();

    virtual std::string toString() const {
        return "";
    }

    virtual void visit(AstVisitor*);

    virtual int getResult() {
        return 0;
    }
};

}
