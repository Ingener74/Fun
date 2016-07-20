#pragma once

#include <vector>
#include <Visitor.h>

namespace fun {

class Interpreter: public Visitor {
public:
    Interpreter();
    virtual ~Interpreter();

    virtual void iterateStatements(class Statement*);
    virtual void iterateExpressions(class Expression*);
    virtual void iterateIds(class Id*);
    virtual void iterateFunctions(class Function*);
    virtual void iterateAssigns(class Assign*);

    virtual void visit(Statement*);
    virtual void visit(Break*);
    virtual void visit(Continue*);
    virtual void visit(For*);
    virtual void visit(Function*);
    virtual void visit(If*);
    virtual void visit(ElseIf*);
    virtual void visit(Else*);
    virtual void visit(IfElseIfsElse*);
    virtual void visit(Import*);
    virtual void visit(Print*);
    virtual void visit(Return*);
    virtual void visit(While*);
    virtual void visit(Class*);
    virtual void visit(Exception*);
    virtual void visit(Throw*);

    virtual void visit(Expression*);
    virtual void visit(Assign*);
    virtual void visit(BinaryOp*);
    virtual void visit(Call*);
    virtual void visit(Dictionary*);
    virtual void visit(Id*);
    virtual void visit(RoundBrackets*);

    virtual void visit(Boolean*);
    virtual void visit(Integer*);
    virtual void visit(Nil*);
    virtual void visit(Real*);
    virtual void visit(String*);

private:
    std::vector<class Terminal*> _terminals;
};

}
