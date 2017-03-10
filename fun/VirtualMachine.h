#pragma once

#include <cstdint>
#include "Utils.h"
#include "Declarations.h"

namespace fun {

struct Instruction {
    enum class OperationCode : uint8_t {
        Push,
        Pop,

        Load,
        Save,

        Jump,
        Test,
        JumpIfTrue,
        JumpIfNotTrue,

        Print, // Temporary

        BinaryOperation,
        UnaryOperation,

        Count,
    };

    OperationCode opCode;
};

struct Load: public Instruction {
};

class VirtualMachine {
public:
    VirtualMachine();
    virtual ~VirtualMachine();

    void run(ByteCodeProgram& program);

    void fetch();

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

private:
    uint8_t* _instructionPointer = nullptr;
};

}
