#pragma once

#include <stack>

#include <AstVisitors/AstVisitor.h>

namespace fun {

class Terminal;

class PrintVisitor: public AstVisitor {
public:
    PrintVisitor();
    virtual ~PrintVisitor();

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
    virtual void visit(class Real*);
    virtual void visit(class Boolean*);
    virtual void visit(class String*);

private:
    std::stack<Terminal*> m_terminals;
    std::stack<Scope*> m_scopes;

    std::string getTabs() const;
};

}
