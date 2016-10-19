#pragma once

#include <vector>
#include <bitset>
#include <unordered_map>
#include <mutex>

#include <Visitor.h>
#include "AST.h"
#include "Debugger.h"
#include "IOperands.h"
#include "IMemory.h"

namespace fun {

class Terminal;

// Уровень стека
class Stack: public Poco::RefCountedObject {
public:
    enum Flag {
        Load, Store, FlagSize
    };
    std::unordered_map<std::string, Terminal*> variables;
    std::bitset<FlagSize> flags;
    Statement* breakIp = nullptr;
    Statement* continueIps = nullptr;
    Statement* catchIps = nullptr;

    Stack* next = nullptr;
};

class Interpreter: public Visitor, public IOperands, public IMemory {
public:
    Interpreter(Debugger* = nullptr);
    virtual ~Interpreter();

    virtual void iterateStatements(Statement*);

    virtual void visit(Break*);
    virtual void visit(Continue*);
    virtual void visit(For*);
    virtual void visit(Function*);
    virtual void visit(Ifs*);
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
    virtual void visit(Dot*);
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
    const std::vector<std::unordered_map<std::string, Terminal*>>& getMemory() const;
    std::vector<std::unordered_map<std::string, Terminal*>>& getMemory();

private:
    std::vector<Terminal*> operands;
    std::vector<std::unordered_map<std::string, Terminal*>> variables;

    bool load = false;
    bool store = false;
    bool break_flag = false;
    bool continue_flag = false;
    bool return_flag = false;

    std::vector<Stack*> stack;

    Terminal* operate(Terminal*, BinaryOperation, Terminal*);

    Debugger* debugger = nullptr;

    template<typename TStatement>
    TStatement* debug(TStatement *stmt) {
        if (debugger)
            debugger->onBeforeStep(stmt);
        return stmt;
    }

    void clearTop();
};

}
