#pragma once

#include <string>
#include <AstNodes/StatementNode.h>

namespace fun {

class Expr;

class Print: public StatementNode {
public:
    Print(Expr*);
    virtual ~Print();

    void accept(AstVisitor*);

private:
    Expr* m_expr;
};

}
