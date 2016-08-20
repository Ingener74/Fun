#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <mutex>
#include <condition_variable>

#include <Poco/Mutex.h>
#include <Poco/Condition.h>

#include <Visitor.h>
#include "Nodes.h"
#include "Debugger.h"

namespace fun {

class Terminal;

class Interpreter;

class Interpreter: public Visitor {
public:
    Interpreter(Debugger* = nullptr);
    virtual ~Interpreter();

    virtual void iterateStatements(Statement*);

    virtual void visit(Break*);
    virtual void visit(Continue*);
    virtual void visit(For*);
    virtual void visit(Function*);
    virtual void visit(If*);
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

    const std::vector<Terminal*>& getOperands() const;
    const std::unordered_map<std::string, Terminal*>& getMemory() const;

private:
    std::vector<Terminal*> operands;
    std::unordered_map<std::string, Terminal*> variables;

    bool load = false;
    bool store = false;
    bool break_flag = false;
    bool continue_flag = false;
    bool return_flag = false;

    // std::vector<Statement*> instructionPointerStack;

    Terminal* operate(Terminal* a, BinaryOp::Op operation, Terminal* b);

    Debugger* debugger = nullptr;

    template<typename TStatement>
    TStatement* debug(TStatement *stmt) {
        if (debugger) debugger->onBeforeStep(stmt);
        return stmt;
    }
};

}
