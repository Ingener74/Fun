#include <cstring>
#include "AST.h"
#include "VirtualMachine.h"

using namespace std;
using namespace Poco;

namespace fun {

VirtualMachine::VirtualMachine()
    : _flags(0) {
}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::run(const ByteCodeProgram& program, const Poco::AutoPtr<Pot>& pot, Debugger* debugger) {
    _debugger = debugger;
    _program = program;
    _pot = pot;
    _instructionPointer = _program.data();
    while (!_flags.test(static_cast<uint8_t>(Flag::Stop))) {
        OpCode opCode;
        read(opCode);
        fassert(opCode < OpCode::Count, "invalid operation code");
        switch (opCode) {
            case OpCode::Push:             push();            break;
            case OpCode::Pop:              pop();             break;
            case OpCode::Memory:           memory();          break;
            case OpCode::Jump:             jump();            break;
            case OpCode::JumpIfTrue:       jumpIfTrue();      break;
            case OpCode::JumpIfNotTrue:    jumpIfNotTrue();   break;
            case OpCode::Print:            print();           break;
            case OpCode::BinaryOperation:  binaryOperation(); break;
            case OpCode::UnaryOperation:   unaryOperation();  break;
            case OpCode::SetFlag:          setFlag();         break;
            case OpCode::ClearFlag:        clearFlag();       break;
            case OpCode::Begin:            begin();           break;
            case OpCode::End:              end();             break;
        }
    }
}

void VirtualMachine::push() {
    Type type = Type::Count;
    read(type);
    fassert(type < Type::Count, "invalid type");
    switch (type) {
    case Type::Nil: {
        if (_flags.test(static_cast<uint8_t>(Flag::Load))) {
            _operands.push_back(new Nil);
        } else if (_flags.test(static_cast<uint8_t>(Flag::Store))) {
            fassert(false, "can't store to terminal");
        }
        break;
    }
    case Type::Boolean: {
        bool value = false;
        read(value);
        if (_flags.test(static_cast<uint8_t>(Flag::Load))) {
            _operands.push_back(new Boolean(value));
        } else if (_flags.test(static_cast<uint8_t>(Flag::Store))) {
            fassert(false, "can't store to terminal");
        }
        break;
    }
    case Type::Integer: {
        long long value = 0;
        read(value);
        if (_flags.test(static_cast<uint8_t>(Flag::Load))) {
            _operands.push_back(new Integer(value));
        } else if (_flags.test(static_cast<uint8_t>(Flag::Store))) {
            fassert(false, "can't store to terminal");
        }
        break;
    }
    case Type::Real: {
        double value = 0.0;
        read(value);
        if (_flags.test(static_cast<uint8_t>(Flag::Load))) {
            _operands.push_back(new Real(value));
        } else if (_flags.test(static_cast<uint8_t>(Flag::Store))) {
            fassert(false, "can't store to terminal");
        }
        break;
    }
    case Type::String: {
        string value;
        read(value);
        if (_flags.test(static_cast<uint8_t>(Flag::Load))) {
            _operands.push_back(new String(value));
        } else if (_flags.test(static_cast<uint8_t>(Flag::Store))) {
            fassert(false, "can't store to terminal");
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

void VirtualMachine::memory() {
    string id;
    read(id);
    if (_flags.test(static_cast<uint8_t>(Flag::Load))) {
        for (auto stackFrameIt = _memory.rbegin(); stackFrameIt != _memory.rend(); ++stackFrameIt) {
            auto variableIt = (*stackFrameIt)->_variables.find(id);
            if (variableIt != (*stackFrameIt)->_variables.end()) {
                _operands.push_back(variableIt->second);
                return;
            }
        }
        fassert(false, "undefined variable " + id);
    } else if (_flags.test(static_cast<uint8_t>(Flag::Store))) {
        fassert(_operands.size(), "have no operands");
        auto& vars = _memory.back()->_variables;
        auto variableIt = vars.find(id);
        if (variableIt == vars.end()) {
            auto insertResult = vars.insert( { id, _operands.back() });
            if (!insertResult.second) {
                fassert(false, "can't create variable " + id);
            }
        } else {
            variableIt->second.assign(_operands.back());
        }
        _operands.pop_back();
    }
}

void VirtualMachine::jump() {
}

void VirtualMachine::jumpIfTrue() {
}

void VirtualMachine::jumpIfNotTrue() {
}

void VirtualMachine::print() {
}

void VirtualMachine::binaryOperation() {
    BinaryOperation binOp = BinaryOperation::Count;
    read(binOp);
    fassert(binOp > BinaryOperation::Assign && binOp < BinaryOperation::Count, "invalid binary operation");
    fassert(_operands.size() >= 2, "not enogth operands");
    auto b = _operands.back();
    _operands.pop_back();
    auto a = _operands.back();
    _operands.pop_back();
    _operands.push_back(operate(a, binOp, b));
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

void VirtualMachine::begin() {
    _memory.push_back(new StackFrame());
}

void VirtualMachine::end() {
    _memory.pop_back();
}

size_t VirtualMachine::count() const {
    return _operands.size();
}

Type VirtualMachine::type(size_t operand) const {
    return _operands.at(operand)->getType();
}

Poco::AutoPtr<Terminal> VirtualMachine::operand(size_t operand) const {
    return _operands.at(operand);
}

bool VirtualMachine::boolean(size_t operand) const {
    return _operands.at(operand)->toBoolean();
}

long long int VirtualMachine::integer(size_t operand) const {
    return _operands.at(operand)->toInteger();
}

double VirtualMachine::real(size_t operand) const {
    return _operands.at(operand)->toReal();
}

string VirtualMachine::str(size_t operand) const {
    return _operands.at(operand)->toString();
}

size_t VirtualMachine::levelCount() const {
    return _memory.size();
}

size_t VirtualMachine::count(size_t memoryLevel) const {
    return _memory.at(memoryLevel)->_variables.size();
}

bool VirtualMachine::has(const string& name) const {
    for (auto it = _memory.rbegin(); it != _memory.rend(); ++it) {
        if ((*it)->_variables.find(name) != (*it)->_variables.end()) {
            return true;
        }
    }
    return false;
}

bool VirtualMachine::has(size_t memoryLevel, const string& name) const {
    if (_memory.at(memoryLevel)->_variables.find(name) != _memory.at(memoryLevel)->_variables.end()) {
        return true;
    }
    return false;
}

Type VirtualMachine::type(const string& name) const {
    auto var = variable(name);
    if (var.isNull())
        return Type::Count;
    return var->getType();
}

Type VirtualMachine::type(size_t memoryLevel, const string& name) const {
    auto var = variable(memoryLevel, name);
    if (var.isNull())
        return Type::Count;
    return var->getType();
}

AutoPtr<Terminal> VirtualMachine::variable(const string& name) const {
    for (auto it = _memory.rbegin(); it != _memory.rend(); ++it) {
        auto varIt = (*it)->_variables.find(name);
        if (varIt != (*it)->_variables.end()) {
            return varIt->second;
        }
    }
    return {};
}

AutoPtr<Terminal> VirtualMachine::variable(size_t memoryLevel, const string& name) const {
    auto varIt = _memory.at(memoryLevel)->_variables.find(name);
    if (varIt != _memory.at(memoryLevel)->_variables.end()) {
        return varIt->second;
    }
    return {};
}

bool VirtualMachine::boolean(const string& name) const {
    auto var = variable(name);
    if (var.isNull())
        return false;
    return var->toBoolean();
}

bool VirtualMachine::boolean(size_t memoryLevel, const string& name) const {
    auto var = variable(memoryLevel, name);
    if (var.isNull())
        return false;
    return var->toBoolean();
}

long long int VirtualMachine::integer(const string& name) const {
    auto var = variable(name);
    if (var.isNull())
        return false;
    return var->toInteger();
}

long long int VirtualMachine::integer(size_t memoryLevel, const string& name) const {
    auto var = variable(memoryLevel, name);
    if (var.isNull())
        return false;
    return var->toInteger();
}

double VirtualMachine::real(const string& name) const {
    auto var = variable(name);
    if (var.isNull())
        return false;
    return var->toReal();
}

double VirtualMachine::real(size_t memoryLevel, const string& name) const {
    auto var = variable(memoryLevel, name);
    if (var.isNull())
        return false;
    return var->toReal();
}

string VirtualMachine::str(const string& name) const {
    auto var = variable(name);
    if (var.isNull())
        return {};
    return var->toString();
}

string VirtualMachine::str(size_t memoryLevel, const string& name) const {
    auto var = variable(memoryLevel, name);
    if (var.isNull())
        return {};
    return var->toString();
}

void VirtualMachine::read(void* data, size_t size) {
    memcpy(data, _instructionPointer, size);
    _instructionPointer += size;
}

void VirtualMachine::read(string& str) {
    uint32_t size = 0;
    read(size);
    vector<char> buffer;
    buffer.resize(size + 1);
    memset(buffer.data(), 0, sizeof(size + 1));
    read(buffer.data(), size);
    str = string(buffer.data());
}

Terminal* VirtualMachine::operate(Terminal* a, BinaryOperation op, Terminal* b) {
    auto seniorType = Terminal::getSeniorBinaryOpType(a, b);
    switch (seniorType) {
    case Type::Integer: {
        auto lhs = a->toInteger();
        auto rhs = b->toInteger();

        switch (op) {
        case BinaryOperation::Add: { return new Integer(lhs + rhs); }
        case BinaryOperation::Sub: { return new Integer(lhs - rhs); }
        case BinaryOperation::Mul: { return new Integer(lhs * rhs); }
        case BinaryOperation::Div: { fassert(rhs != 0, "divide by zero"); return new Integer(lhs / rhs); }
        case BinaryOperation::Mod: { fassert(rhs != 0, "divide by zero"); return new Integer(lhs % rhs); }

        case BinaryOperation::LShift:     { return new Integer(lhs << rhs); }
        case BinaryOperation::RShift:     { return new Integer(lhs >> rhs); }
        case BinaryOperation::BinaryOr:  { return new Integer(lhs | rhs); }
        case BinaryOperation::BinaryAnd: { return new Integer(lhs & rhs); }
        case BinaryOperation::BinaryXor: { return new Integer(lhs ^ rhs); }

        case BinaryOperation::LogicOr:  { return new Boolean(lhs || rhs); }
        case BinaryOperation::LogicAnd: { return new Boolean(lhs && rhs); }

        case BinaryOperation::Equal:      { return new Boolean(lhs == rhs); }
        case BinaryOperation::NotEqual:  { return new Boolean(lhs != rhs); }
        case BinaryOperation::More:       { return new Boolean(lhs >  rhs); }
        case BinaryOperation::MoreEqual: { return new Boolean(lhs >= rhs); }
        case BinaryOperation::Less:       { return new Boolean(lhs <  rhs); }
        case BinaryOperation::LessEqual: { return new Boolean(lhs <= rhs); }
        default:
            fassertl(false, a->loc + b->loc, "unsupported operation");
        }
        break;
    }
    case Type::Real: {
        auto lhs = a->toReal();
        auto rhs = b->toReal();

        switch (op) {
        case BinaryOperation::Add: { return new Real(lhs + rhs); }
        case BinaryOperation::Sub: { return new Real(lhs - rhs); }
        case BinaryOperation::Mul: { return new Real(lhs * rhs); }
        case BinaryOperation::Div: { fassert(rhs != 0.0, "devide by zero"); return new Real(lhs / rhs); }

        case BinaryOperation::LogicOr:  { return new Boolean(Real::isTrue(lhs) || Real::isTrue(rhs)); }
        case BinaryOperation::LogicAnd: { return new Boolean(Real::isTrue(lhs) && Real::isTrue(rhs)); }

        case BinaryOperation::Equal:      { return new Boolean(lhs == rhs); }
        case BinaryOperation::NotEqual:  { return new Boolean(lhs != rhs); }
        case BinaryOperation::More:       { return new Boolean(lhs >  rhs); }
        case BinaryOperation::MoreEqual: { return new Boolean(lhs >= rhs); }
        case BinaryOperation::Less:       { return new Boolean(lhs <  rhs); }
        case BinaryOperation::LessEqual: { return new Boolean(lhs <= rhs); }
        default:
            fassertl(false, a->loc + b->loc, "unsupported operation");
        }
        break;
    }
    case Type::String: {
        auto lhs = a->toString();
        auto rhs = b->toString();

        switch (op) {
        case BinaryOperation::Add: { return new String(lhs + rhs); }

        case BinaryOperation::LogicOr:  { return new Boolean(String::isTrue(lhs) || String::isTrue(rhs)); }
        case BinaryOperation::LogicAnd: { return new Boolean(String::isTrue(lhs) && String::isTrue(rhs)); }

        case BinaryOperation::LShift:     { return new String(lhs + rhs); }
        case BinaryOperation::RShift:     { return new String(lhs + rhs); }

        case BinaryOperation::More:       { return new Boolean(lhs.size() >  rhs.size()); }
        case BinaryOperation::MoreEqual: { return new Boolean(lhs.size() >= rhs.size()); }
        case BinaryOperation::Less:       { return new Boolean(lhs.size() <  rhs.size()); }
        case BinaryOperation::LessEqual: { return new Boolean(lhs.size() <= rhs.size()); }

        case BinaryOperation::Equal:      { return new Boolean(lhs == rhs); }
        case BinaryOperation::NotEqual:  { return new Boolean(lhs != rhs); }
        default:
            fassertl(false, a->loc + b->loc, "unsupported operation");
        }
        break;
    }
    case Type::Boolean:{
        auto lhs = a->toBoolean();
        auto rhs = b->toBoolean();

        switch (op) {
        case BinaryOperation::More:       { return new Boolean(lhs >  rhs); }
        case BinaryOperation::MoreEqual: { return new Boolean(lhs >= rhs); }
        case BinaryOperation::Less:       { return new Boolean(lhs <  rhs); }
        case BinaryOperation::LessEqual: { return new Boolean(lhs <= rhs); }

        case BinaryOperation::Equal:      { return new Boolean(lhs == rhs); }
        case BinaryOperation::NotEqual:  { return new Boolean(lhs != rhs); }

        case BinaryOperation::LogicOr:  { return new Boolean(lhs || rhs); }
        case BinaryOperation::LogicAnd: { return new Boolean(lhs && rhs); }

        default:
            fassertl(false, a->loc + b->loc, "unsupported operation");
        }
        break;
    }
    case Type::Nil: {
        switch (op) {
        case BinaryOperation::LogicAnd: { return new Boolean(false); }
        case BinaryOperation::LogicOr: { return new Boolean(false); }

        case BinaryOperation::Equal:      { return new Boolean(true); }
        case BinaryOperation::NotEqual:  { return new Boolean(false); }

        default:
            fassertl(false, a->loc + b->loc, "unsupported operation");
        }
        break;
    }
    default:
        fassertl(false, a->loc + b->loc, "unsupported operation");
    }
    return nullptr;
}

}
