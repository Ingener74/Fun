#pragma once

#include <vector>
#include <string>

#include <Visitor.h>

namespace fun {

class Printer: public Visitor {
public:
    Printer();
    virtual ~Printer();

    virtual void iterateStatements(Statement*);
    virtual void iterateExpressions(Expression*);
    virtual void iterateIds(Id*);
    virtual void iterateFunctions(Function*);
    virtual void iterateAssigns(Assign*);

//    virtual void visit(Statement*);
    virtual void visit(Break*);
    virtual void visit(Continue*);
    virtual void visit(Class*);
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
    virtual void visit(Exception*);
    virtual void visit(Throw*);

//    virtual void visit(Expression*);
    virtual void visit(Assign*);
    virtual void visit(BinaryOp*);
    virtual void visit(Call*);
    virtual void visit(Dictionary*);
    virtual void visit(Id*);
    virtual void visit(Index*);
    virtual void visit(RoundBrackets*);

//    virtual void visit(Terminal*);
    virtual void visit(Boolean*);
    virtual void visit(Integer*);
    virtual void visit(Nil*);
    virtual void visit(Real*);
    virtual void visit(String*);

private:
    int _scopeLevel = 0;

    std::string indents() const;
};

}
