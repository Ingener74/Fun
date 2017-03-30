#pragma once

#include <cstdint>
#include <bitset>
#include <unordered_map>
#include <array>
#include <Poco/AutoPtr.h>
#include <Poco/RefCountedObject.h>
#include "Utils.h"
#include "IOperands.h"
#include "IMemory.h"
#include "Declarations.h"

namespace fun {

class Terminal;
class Pot;
class Debugger;

class VirtualMachine: public IOperands, public IMemory {
public:
    VirtualMachine();
    virtual ~VirtualMachine();

    void run(const ByteCodeProgram& program, const Poco::AutoPtr<Pot>& pot, Debugger* debugger);

    void push();
    void pop();

    void memory();

    void jump();
    void jumpIfTrue();
    void jumpIfNotTrue();

    void print();

    void binaryOperation();
    void unaryOperation();

    void setFlag();
    void clearFlag();

    void begin();
    void end();

    // IOperands
    virtual size_t count() const override;
    virtual Type type(size_t operand) const override;
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

    virtual Type type(const std::string& name) const override;
    virtual Type type(size_t memoryLevel, const std::string& name) const override;

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

private:
    void read(void* data, size_t size);
    template<typename T>
    void read(T& t);
    void read(std::string& str);

    Terminal* operate(Terminal*, BinaryOperation, Terminal*);

    struct StackFrame: public Poco::RefCountedObject {
        std::unordered_map<std::string, Poco::AutoPtr<Terminal>> _variables;
    };

    struct ThreadContext: public Poco::RefCountedObject {
//        std::bitset<static_cast<uint8_t>(Flag::Count)> _flags;
        std::vector<Poco::AutoPtr<StackFrame>> _memory;
        std::vector<Poco::AutoPtr<Terminal>> _operands;
        uint8_t* _ip = nullptr;
    };

    std::vector<Poco::AutoPtr<ThreadContext>> _threadsData;

//    std::bitset<static_cast<uint8_t>(Flag::Count)> _flags;

    std::array<int, FlagCount> _flags;
    std::vector<Poco::AutoPtr<StackFrame>> _memory;
    std::vector<Poco::AutoPtr<Terminal>> _operands;
    uint16_t _savedOperands;

    ByteCodeProgram _program;
    uint8_t* _instructionPointer = nullptr;
    Poco::AutoPtr<Pot> _pot;
    Debugger* _debugger = nullptr;
};

template<typename T>
inline void VirtualMachine::read(T& t) {
    read(&t, sizeof(t));
}

}
