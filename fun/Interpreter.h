#pragma once

#include <vector>
#include <bitset>
#include <unordered_map>
#include <mutex>

#include "Visitor.h"
#include "AST.h"
#include "Debugger.h"
#include "IOperands.h"
#include "IMemory.h"

namespace fun {

class Terminal;

// Уровень стека
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

    // IOperand
    virtual size_t count() const override;

    virtual Terminal::Type type(size_t operand) const override;

    virtual Poco::AutoPtr<Terminal> operand(size_t operand) const override;

    virtual bool boolean(size_t operand) const override;

    virtual long long int integer(size_t operand) const override;

    virtual double real(size_t operand) const override;

    virtual std::string str(size_t operand) const override;

    // IMemory
    virtual size_t levelCount() const override;
    virtual size_t count(size_t memoryLevel) const override;

    virtual bool has(const std::string& name) const override;
    virtual bool has(size_t memoryLevel, const std::string& name) const override;

    virtual Terminal::Type type(const std::string& name) const override;
    virtual Terminal::Type type(size_t memoryLevel, const std::string& name) const override;

    virtual Poco::AutoPtr<Terminal> variable(const std::string& name) const override;
    virtual Poco::AutoPtr<Terminal> variable(size_t memoryLevel, const std::string& name) const override;

    virtual bool boolean(const std::string& name) const override;
    virtual bool boolean(size_t memoryLevel, const std::string& name) const override;

    virtual long long int integer(const std::string& name) const override;
    virtual long long int integer(size_t memoryLevel, const std::string& name) const override;

    virtual double real(const std::string& name) const override;
    virtual double real(size_t memoryLevel, const std::string& name) const override;

    virtual std::string str(const std::string& name) const override;
    virtual std::string str(size_t memoryLevel, const std::string& name) const override;

    Interpreter* setDebugger(Debugger* debugger);

private:
    void iterate();

    Terminal* operate(Terminal*, BinaryOperation, Terminal*);

    template<typename T> T* debug(T* stmt);

    Statement* next(Statement* stmt);

    bool load = false;
    bool store = false;
    bool break_flag = false;
    bool continue_flag = false;
    bool return_flag = false;

    Debugger* _debugger = nullptr;

    class StackLevel: public Poco::RefCountedObject {
    public:
        StackLevel() = default;
        virtual ~StackLevel() = default;

        std::unordered_map<std::string, Poco::AutoPtr<Terminal>> variables;
        Statement* breakIp = nullptr;
        Statement* continueIp = nullptr;
        Statement* catchIp = nullptr;
        Statement* returnIp = nullptr;
        Statement* nextIfIp = nullptr;
        Statement* ifsEndIp = nullptr;

        Statement* nextIp = nullptr;
    };

    std::vector<Poco::AutoPtr<Terminal>> operands;
    std::vector<Poco::AutoPtr<StackLevel>> stack;
    Statement* ip = nullptr;
};

inline Interpreter* Interpreter::setDebugger(Debugger* debugger) {
    _debugger = debugger;
    return this;
}

template<typename T>
inline T* Interpreter::debug(T* stmt) {
    if (_debugger)
        _debugger->onBeforeStep(stmt);
    return stmt;
}

}
