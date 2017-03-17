#pragma once

#include <cstdint>
#include <bitset>
#include <Poco/AutoPtr.h>
#include "Utils.h"
#include "Declarations.h"

namespace fun {

class Terminal;

class VirtualMachine {
public:
    VirtualMachine();
    virtual ~VirtualMachine();

    void run(const ByteCodeProgram& program);

    void push();
    void pop();

    void load();
    void save();

    void jump();
    void test();
    void jumpIfTrue();
    void jumpIfNotTrue();

    void print();

    void binaryOperation();
    void unaryOperation();

    void setFlag();
    void clearFlag();

private:
    void read(void* data, size_t size);
    template<typename T>
    void read(T& t);
    void read(std::string& str, uint32_t size);

    std::bitset<static_cast<uint8_t>(Flag::Count)> _flags;

    ByteCodeProgram _program;
    uint8_t* _instructionPointer = nullptr;

    std::vector<Poco::AutoPtr<Terminal>> _operands;
};

template<typename T>
inline void VirtualMachine::read(T& t) {
    read(&t, sizeof(t));
}

}
