#include <cstring>
#include "AST.h"
#include "VirtualMachine.h"

using namespace std;

namespace fun {

VirtualMachine::VirtualMachine() {
}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::run(const ByteCodeProgram& program) {
    _program = program;
    _instructionPointer = _program.data();
    while (_flags.test(static_cast<uint8_t>(Flag::Stop))) {
        OpCode opCode;
        read(opCode);
        fassert(opCode < OpCode::Count, "invalid operation code");
        switch (opCode) {
            case OpCode::Push:             push();            break;
            case OpCode::Pop:              pop();             break;
            case OpCode::Load:             load();            break;
            case OpCode::Save:             save();            break;
            case OpCode::Jump:             jump();            break;
            case OpCode::Test:             test();            break;
            case OpCode::JumpIfTrue:       jumpIfTrue();      break;
            case OpCode::JumpIfNotTrue:    jumpIfNotTrue();   break;
            case OpCode::Print:            print();           break;
            case OpCode::BinaryOperation:  binaryOperation(); break;
            case OpCode::UnaryOperation:   unaryOperation();  break;
            case OpCode::SetFlag:          setFlag();         break;
            case OpCode::ClearFlag:        clearFlag();       break;
        }
    }
}

void VirtualMachine::push() {
    Type type = Type::Count;
    read(type);
    fassert(type < Type::Count, "invalid type");
    switch (type) {
    case Type::Nil: {
        break;
    }
    case Type::Boolean: {
        bool value = false;
        read(value);
        if (_flags.test(static_cast<uint8_t>(Flag::Load))) {
            _operands.push_back(new Boolean(value));
        }
        break;
    }
    case Type::Integer: {
        long long value = 0;
        read(value);
        if (_flags.test(static_cast<uint8_t>(Flag::Load))) {
            _operands.push_back(new Integer(value));
        }
        break;
    }
    case Type::Real: {
        double value = 0.0;
        read(value);
        if (_flags.test(static_cast<uint8_t>(Flag::Load))) {
            _operands.push_back(new Real(value));
        }
        break;
    }
    case Type::String: {
        uint32_t size = 0;
        read(size);
        string value;
        read(value, size);
        if (_flags.test(static_cast<uint8_t>(Flag::Load))) {
            _operands.push_back(new String(value));
        }
        break;
    }
    case Type::Object:
        break;
    case Type::Function:
        break;
    case Type::Dictionary:
        break;
    case Type::List:
        break;
    }
}

void VirtualMachine::pop() {
}

void VirtualMachine::load() {
}

void VirtualMachine::save() {
}

void VirtualMachine::jump() {
}

void VirtualMachine::test() {
}

void VirtualMachine::jumpIfTrue() {
}

void VirtualMachine::jumpIfNotTrue() {
}

void VirtualMachine::print() {
}

void VirtualMachine::binaryOperation() {
    BinaryOperation binOp = BinaryOperation::NOP;
    read(binOp);
    fassert(binOp > BinaryOperation::NOP && binOp < BinaryOperation::Count, "invalid binary operation");

    switch (binOp) {
    case BinaryOperation::ADD: {
        break;
    }
    case BinaryOperation::SUB: {
        break;
    }
    case BinaryOperation::MUL: {
        break;
    }
    case BinaryOperation::DIV: {
        break;
    }
    case BinaryOperation::MOD: {
        break;
    }
    case BinaryOperation::BINARY_OR: {
        break;
    }
    case BinaryOperation::BINARY_AND: {
        break;
    }
    case BinaryOperation::BINARY_XOR: {
        break;
    }
    case BinaryOperation::LOGIC_OR: {
        break;
    }
    case BinaryOperation::LOGIC_AND: {
        break;
    }
    case BinaryOperation::LSHIFT: {
        break;
    }
    case BinaryOperation::RSHIFT: {
        break;
    }
    case BinaryOperation::LESS: {
        break;
    }
    case BinaryOperation::MORE: {
        break;
    }
    case BinaryOperation::LESS_EQUAL: {
        break;
    }
    case BinaryOperation::MORE_EQUAL: {
        break;
    }
    case BinaryOperation::EQUAL: {
        break;
    }
    case BinaryOperation::NOT_EQUAL: {
        break;
    }
    }
}

void VirtualMachine::unaryOperation() {
}

void VirtualMachine::setFlag() {
    Flag flag = Flag::Load;
    read(flag);
    fassert(flag >= Flag::Load && flag < Flag::Count, "invalid flag");
    _flags.set(static_cast<uint8_t>(flag), true);
}

void VirtualMachine::clearFlag() {
    Flag flag = Flag::Load;
    read(flag);
    fassert(flag >= Flag::Load && flag < Flag::Count, "invalid flag");
    _flags.reset(static_cast<uint8_t>(flag));
}

void VirtualMachine::read(void* data, size_t size) {
    memcpy(data, _instructionPointer, size);
    _instructionPointer += size;
}

void VirtualMachine::read(std::string& str, uint32_t size) {
    fassert(false, "not implemented");
}

}

