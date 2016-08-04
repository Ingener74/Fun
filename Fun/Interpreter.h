#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <Visitor.h>

namespace fun {

class Terminal;

using Operands = std::vector<Terminal*>;

//using Memory = std::vector<std::unordered_map<std::string, std::pair<int, Terminal*>>>;
using Memory = std::unordered_map<std::string, std::pair<int, Terminal*>>;

class Breakpoint {
public:
    Breakpoint(const std::string& module = {}, int line = 0) :
            module(module), line(line) {
    }
    virtual ~Breakpoint() {
    }

    std::string module;
    int line;
};

using Breakpoints = std::vector<Breakpoint>;

class Interpreter;

class Debugger {
public:
    Debugger() = default;
    virtual ~Debugger() = default;

    virtual void setBreakpoint(const Breakpoint&) = 0;
    virtual void enableBreakpoint(const Breakpoint&) = 0;
    virtual void disableBreakpoint(const Breakpoint&) = 0;
    virtual void removeBreakpoint(const Breakpoint&) = 0;
    virtual const std::vector<Breakpoint>& getBreakpoints() const = 0;

    virtual void onCatchBreakpoint(const Breakpoint&) = 0;

    virtual void onBeforeStep() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void stepOver() = 0;
    virtual void stepIn() = 0;
    virtual void stepOut() = 0;

    virtual void onOperandsChanged(const Operands&) = 0;
    virtual void onMemoryChanged(const Memory&) = 0;
};

class Interpreter: public Visitor {
public:
    Interpreter(Debugger* = nullptr);
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

    const Operands& getOperands() const;
    const Memory& getMemory() const;

private:
    Operands operands;

//    std::vector<>
    Memory variables;

    std::map<std::string, Function*> functions;

//    std::vector<std::map<std::string, std::pair<int, Terminal*>>> vars;

    template<typename T, typename ... Args>
    T* create(Args&& ... args) {
        std::unique_ptr<T> node(new T(std::forward<Args>(args)...));
        T* result = node.get();
        mem.push_back(std::move(node));
        return result;
    }
    std::vector<std::unique_ptr<Terminal>> mem;

    bool load_flag = false;
    bool store_flag = false;
    bool break_flag = false;
    bool continue_flag = false;

    Terminal* operate(Terminal* a, BinaryOp::Op operation, Terminal* b);

    Debugger* debugger = nullptr;
};

}
