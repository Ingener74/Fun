#pragma once

#include <vector>
#include <map>
#include <Visitor.h>

namespace fun {

class Terminal;

class Interpreter: public Visitor {
public:
    Interpreter();
    virtual ~Interpreter();

    virtual void iterateStatements(Statement*);
    virtual void iterateExpressions(Expression*);
    virtual void iterateIds(Id*);
    virtual void iterateFunctions(Function*);
    virtual void iterateAssigns(Assign*);
    virtual void iterateElseIfs(ElseIf*);

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
    std::vector<Terminal*> operands;

//    std::vector<>
    std::map<std::string, std::pair<int, Terminal*>> variables;

    template<typename T, typename ... Args>
    T* create(Args&& ... args) {
        std::unique_ptr<T> node(new T(std::forward<Args>(args)...));
        T* result = node.get();
        mem.push_back(std::move(node));
        return result;
    }
    std::vector<std::unique_ptr<Terminal>> mem;

    enum Operation{
        Load, Store, Undefined,
    };
    Operation operation = Undefined;

    Terminal* operate(Terminal* a, BinaryOp::Op operation, Terminal* b);
};

}
