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
    std::unordered_map<std::string, Poco::AutoPtr<Terminal>> variables;
    Statement* breakIp = nullptr;
    Statement* continueIps = nullptr;
    Statement* catchIps = nullptr;
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

    const std::vector<Poco::AutoPtr<Terminal>>& getOperands() const override;
    std::vector<Poco::AutoPtr<Terminal>>& getOperands() override;
    const std::vector<std::unordered_map<std::string, Poco::AutoPtr<Terminal>>>& getMemory() const override;
    std::vector<std::unordered_map<std::string, Poco::AutoPtr<Terminal>>>& getMemory() override;

    Interpreter* setDebugger(Debugger* debugger);

private:
    std::vector<Poco::AutoPtr<Terminal>> operands;
    std::vector<std::unordered_map<std::string, Poco::AutoPtr<Terminal>>> variables;

    enum Flag {
        Load, Store, FlagsCount
    };
    std::bitset<FlagsCount> flags;

    bool load = false;
    bool store = false;
    bool break_flag = false;
    bool continue_flag = false;
    bool return_flag = false;

    std::vector<Poco::AutoPtr<Stack>> stack;
    size_t stackTop = 0;

    Terminal* operate(Terminal*, BinaryOperation, Terminal*);

    Debugger* debugger = nullptr;

    template<typename TStatement>
    TStatement* debug(TStatement *stmt) {
        if (debugger)
            debugger->onBeforeStep(stmt);
        return stmt;
    }
};

inline Interpreter* Interpreter::setDebugger(Debugger* debugger) {
    this->debugger = debugger;
    return this;
}

}
