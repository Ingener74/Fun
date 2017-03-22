#pragma once

#include <cstdint>
#include <bitset>
#include <Poco/AutoPtr.h>
#include "Utils.h"
#include "IOperands.h"
#include "Declarations.h"

namespace fun {

class Terminal;

class VirtualMachine: public IOperands {
public:
    VirtualMachine();
    virtual ~VirtualMachine();

    void run(const ByteCodeProgram& program);

    void push();
    void pop();

    void memory();

    void jump();
    void test();
    void jumpIfTrue();
    void jumpIfNotTrue();

    void print();

    void binaryOperation();
    void unaryOperation();

    void setFlag();
    void clearFlag();

    // IOperands
    virtual size_t count() const override;

    virtual Type type(size_t operand) const override;

    virtual Poco::AutoPtr<Terminal> operand(size_t operand) const override;

    virtual bool boolean(size_t operand) const override;

    virtual long long int integer(size_t operand) const override;

    virtual double real(size_t operand) const override;

    virtual std::string str(size_t operand) const override;

private:
    void read(void* data, size_t size);
    template<typename T>
    void read(T& t);
    void read(std::string& str);

    Terminal* operate(Terminal*, BinaryOperation, Terminal*);

    std::bitset<static_cast<uint8_t>(Flag::Count)> _flags;
    std::vector<Poco::AutoPtr<Terminal>> _operands;
    ByteCodeProgram _program;
    uint8_t* _instructionPointer = nullptr;
};

template<typename T>
inline void VirtualMachine::read(T& t) {
    read(&t, sizeof(t));
}

}
