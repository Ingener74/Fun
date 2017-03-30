#pragma once

#include <vector>

class Statement;

enum class BuildType : uint8_t {
    Release,
    Debug,

    Count,
};

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
    Assign,
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    BinaryOr,
    BinaryAnd,
    BinaryXor,
    LogicOr,
    LogicAnd,
    LShift,
    RShift,
    Less,
    More,
    LessEqual,
    MoreEqual,
    Equal,
    NotEqual,

    Count,
};

enum class OpCode : uint8_t {
    Push,
    Pop,
    Memory,
    Jump,
    JumpIfTrue,
    JumpIfNotTrue,
    Print, // Temporary
    BinaryOperation,
    UnaryOperation,
    SetFlag,
    ClearFlag,
    Nop,
    Begin,
    End,

    SaveNumberOfOperands,
    InvertOperands,

    Count,
};

enum Flag : uint8_t {
    FlagLoad,
    FlagStore,
    FlagStop,

    FlagCount,
};

typedef std::vector<Statement*>     Program;
typedef Program::iterator           InstructionPointer;

typedef std::vector<unsigned char>  ByteCodeProgram;
typedef ByteCodeProgram::iterator   ByteCodeInstructionPointer;

typedef uint64_t                    StatementId;

