#pragma once

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>

namespace fun {

class Visitor: public Poco::RefCountedObject {
public:
    using Ptr = Poco::AutoPtr<Visitor>;

    Visitor();
    virtual ~Visitor();

    virtual void iterateStatements(class Statement*){}

    virtual void visit(class Statement*){}
    virtual void visit(class Break*){}
    virtual void visit(class Continue*){}
    virtual void visit(class Class*){}
    virtual void visit(class For*){}
    virtual void visit(class Function*){}
    virtual void visit(class Ifs*){}
    virtual void visit(class If*){}
    virtual void visit(class Import*){}
    virtual void visit(class Print*){}
    virtual void visit(class Return*){}
    virtual void visit(class While*){}
    virtual void visit(class Exception*){}
    virtual void visit(class Throw*){}

    virtual void visit(class Expression*){}
    virtual void visit(class Assign*){}
    virtual void visit(class BinaryOp*){}
    virtual void visit(class Dot*){}
    virtual void visit(class Call*){}
    virtual void visit(class Dictionary*){}
    virtual void visit(class Id*){}
    virtual void visit(class Index*){}
    virtual void visit(class RoundBrackets*){}

    virtual void visit(class Terminal*){}
    virtual void visit(class Boolean*){}
    virtual void visit(class Integer*){}
    virtual void visit(class Nil*){}
    virtual void visit(class Real*){}
    virtual void visit(class String*){}
};

}
