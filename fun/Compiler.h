#pragma once

#include "Declarations.h"
#include "Visitor.h"

namespace fun {

class Compiler: public Visitor {
public:
    Compiler();
    virtual ~Compiler();

    virtual void visit(Statement*);
    virtual void visit(Break*);
    virtual void visit(Continue*);
    virtual void visit(Class*);
    virtual void visit(For*);
    virtual void visit(Function*);
    virtual void visit(Ifs*);
    virtual void visit(If*);
    virtual void visit(Import*);
    virtual void visit(Print*);
    virtual void visit(Return*);
    virtual void visit(While*);
    virtual void visit(Exception*);
    virtual void visit(Throw*);

    virtual void visit(Expression*);
    virtual void visit(Assign*);
    virtual void visit(BinaryOp*);
    virtual void visit(Dot*);
    virtual void visit(Call*);
    virtual void visit(Dictionary*);
    virtual void visit(Id*);
    virtual void visit(Index*);
    virtual void visit(RoundBrackets*);

    virtual void visit(Terminal*);
    virtual void visit(Boolean*);
    virtual void visit(Integer*);
    virtual void visit(Nil*);
    virtual void visit(Real*);
    virtual void visit(String*);

    virtual void visit(AddFrame*);
    virtual void visit(RemoveFrame*);
    virtual void visit(Jump*);
    virtual void visit(ConditionJump*);

    const ByteCodeProgram& getProgram() const;

private:
    ByteCodeProgram _program;
};

}
