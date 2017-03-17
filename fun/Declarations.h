#pragma once

#include <vector>

class Statement;

enum class Type : uint8_t {
    Nil,
    Boolean,
    Integer,
    Real,
    String,
    Object,
    Function,
    Dictionary,
    List,
    Count,
};

enum class BinaryOperation : uint8_t {
    NOP,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    BINARY_OR,
    BINARY_AND,
    BINARY_XOR,
    LOGIC_OR,
    LOGIC_AND,
    LSHIFT,
    RSHIFT,
    LESS,
    MORE,
    LESS_EQUAL,
    MORE_EQUAL,
    EQUAL,
    NOT_EQUAL,
    Count,
};

enum class OpCode : uint8_t {
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
    SetFlag,
    ClearFlag,
    Count,
};

enum class Flag : uint8_t {
    Load,
    Store,
    True,
    Stop,
    Count,
};

using Program = std::vector<Statement*>;
using InstructionPointer = Program::iterator;

using ByteCodeProgram = std::vector<unsigned char>;
using ByteCodeInstructionPointer = ByteCodeProgram::iterator;

