#pragma once

namespace fun {

class Visitor {
public:
    Visitor();
    virtual ~Visitor();

    virtual void visit(class Node*){}
    virtual void visit(class ArgumentList*){}
    virtual void visit(class ExpressionList*){}
    virtual void visit(class Scope*){}

    virtual void visit(class Statement*){}
    virtual void visit(class Function*){}
    virtual void visit(class If*){}
    virtual void visit(class While*){}
    virtual void visit(class Import*){}
    virtual void visit(class Print*){}

    virtual void visit(class Expression*){}
    virtual void visit(class Assign*){}
    virtual void visit(class BinaryOp*){}
    virtual void visit(class Call*){}
    virtual void visit(class Id*){}
    virtual void visit(class Integer*){}
    virtual void visit(class Real*){}
    virtual void visit(class Boolean*){}
    virtual void visit(class String*){}
};

}
