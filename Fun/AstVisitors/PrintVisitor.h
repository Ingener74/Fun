#pragma once

#include <stack>

#include <AstVisitors/AstVisitor.h>

namespace fun {

class PrintVisitor: public AstVisitor {
public:
    PrintVisitor();
    virtual ~PrintVisitor();

    virtual void visit(class ArgumentList*);
    virtual void visit(class ExpressionList*);
    virtual void visit(class Scope*);

    virtual void visit(class Function*);
    virtual void visit(class If*);
    virtual void visit(class While*);
    virtual void visit(class Import*);
    virtual void visit(class Print*);

    virtual void visit(class Expression*);
    virtual void visit(class Assign*);
    virtual void visit(class BinaryOp*);
    virtual void visit(class Call*);
    virtual void visit(class Id*);
    virtual void visit(class Integer*);

private:
    std::stack<Integer*> m_integers;
    std::stack<Scope*> m_scopes;

    std::string getTabs() const;
};

}
