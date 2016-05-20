#pragma once

#include <AstNodes/StatementNode.h>

namespace fun {

class Expr;
class Scope;
class AstVisitor;

class IfStatement: public StatementNode {
public:
    IfStatement(Expr* condition, Scope* then_scope, Scope* else_scope = nullptr);
    virtual ~IfStatement();

    void accept(AstVisitor*);
};

}
