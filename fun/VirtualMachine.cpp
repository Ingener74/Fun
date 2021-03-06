#include <cstring>
#include "AST.h"
#include "Debugger.h"
#include "VirtualMachine.h"

using namespace std;
using namespace Poco;

namespace fun {

VirtualMachine::VirtualMachine() {
    _flags[FlagLoad] = 0;
    _flags[FlagStore] = 0;
    _flags[FlagStop] = 0;
}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::run(const ByteCodeProgram& program, const Poco::AutoPtr<Pot>& pot, Debugger* debugger) {

    _debugger = debugger;
    _program = program;
    _pot = pot;
    _instructionPointer = _program.data();

    bool hasSourceHash = false;
    read(hasSourceHash);

    string sourceHash;
    if (hasSourceHash)
        read(sourceHash);

    read(_debugInfo);

    while (!_flags[FlagStop]) {
        OpCode opCode;
        read(opCode);
        fassert(opCode < OpCode::Count, "invalid operation code");

        AutoPtr<Statement> stmt;
        if (_debugInfo) {
            StatementId statementId = InvalidStatementId;
            read(statementId);
            stmt = _pot->getStatement(statementId);
        }

        switch (opCode) {
            case OpCode::Push:             push(stmt);            break;
            case OpCode::Pop:              pop(stmt);             break;
            case OpCode::Memory:           memory(stmt);          break;
            case OpCode::Jump:             jump(stmt);            break;
            case OpCode::JumpIfTrue:       jumpIfTrue(stmt);      break;
            case OpCode::JumpIfNotTrue:    jumpIfNotTrue(stmt);   break;
            case OpCode::Print:            print(stmt);           break;
            case OpCode::BinaryOperation:  binaryOperation(stmt); break;
            case OpCode::UnaryOperation:   unaryOperation(stmt);  break;
            case OpCode::SetFlag:          setFlag(stmt);         break;
            case OpCode::ClearFlag:        clearFlag(stmt);       break;
            case OpCode::Begin:            begin(stmt);           break;
            case OpCode::End:              end(stmt);             break;
        }
    }

//    fassert(_operands.empty(), "stack of operands not empty at the end of program");
    fassert(_memory.empty(), "stack of memory not empty at the end of program");
    fassert(_flags[FlagLoad] == 0, "load flag balance not 0");
    fassert(_flags[FlagStore] == 0, "store flag balance not 0");
}

void VirtualMachine::push(Statement* stmt) {
    Type type = Type::Count;
    read(type);
    fassert(type < Type::Count, "invalid type");
    switch (type) {
    case Type::Nil: {
        if (_flags[FlagLoad]) {
            _operands.push_back(new Nil);
        } else if (_flags[FlagStore]) {
            fasserts(false, stmt, "can't store to terminal");
        }
        break;
    }
    case Type::Boolean: {
        bool value = false;
        read(value);
        if (_flags[FlagLoad]) {
            _operands.push_back(new Boolean(value));
        } else if (_flags[FlagStore]) {
            fassert(false, "can't store to terminal");
        }
        break;
    }
    case Type::Integer: {
        long long value = 0;
        read(value);
        if (_flags[FlagLoad]) {
            _operands.push_back(new Integer(value));
        } else if (_flags[FlagStore]) {
            fassert(false, "can't store to terminal");
        }
        break;
    }
    case Type::Real: {
        double value = 0.0;
        read(value);
        if (_flags[FlagLoad]) {
            _operands.push_back(new Real(value));
        } else if (_flags[FlagStore]) {
            fassert(false, "can't store to terminal");
        }
        break;
    }
    case Type::String: {
        string value;
        read(value);
        if (_flags[FlagLoad]) {
            _operands.push_back(new String(value));
        } else if (_flags[FlagStore]) {
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

void VirtualMachine::pop(Statement*) {
}

void VirtualMachine::memory(Statement* stmt) {
    string id;
    read(id);
    if (_flags[FlagStore]) {
        fasserts(_operands.size(), stmt, "have no operands");
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
    if (_flags[FlagLoad]) {
        for (auto stackFrameIt = _memory.rbegin(); stackFrameIt != _memory.rend(); ++stackFrameIt) {
            auto variableIt = (*stackFrameIt)->_variables.find(id);
            if (variableIt != (*stackFrameIt)->_variables.end()) {
                _operands.push_back(variableIt->second);
                return;
            }
        }
        fasserts(false, stmt, "undefined variable " + id);
    }
}

void VirtualMachine::jump(Statement*) {
}

void VirtualMachine::jumpIfTrue(Statement*) {
}

void VirtualMachine::jumpIfNotTrue(Statement*) {
}

void VirtualMachine::print(Statement*) {
}

void VirtualMachine::binaryOperation(Statement* stmt) {
    BinaryOperation binOp = BinaryOperation::Count;
    read(binOp);
    fasserts(binOp > BinaryOperation::Assign && binOp < BinaryOperation::Count, stmt, "invalid binary operation");
    fasserts(_operands.size() >= 2, stmt, "not enogth operands");
    auto b = _operands.back();
    _operands.pop_back();
    auto a = _operands.back();
    _operands.pop_back();
    _operands.push_back(operate(a, binOp, b));
}

void VirtualMachine::unaryOperation(Statement*) {
}

void VirtualMachine::setFlag(Statement* stmt) {
    Flag flag = FlagCount;
    read(flag);
    fasserts(flag < FlagCount, stmt, "invalid flag");
    fasserts(_flags[flag] >= 0, stmt, "no flags");
    _flags[flag]++;
}

void VirtualMachine::clearFlag(Statement* stmt) {
    Flag flag = FlagCount;
    read(flag);
    fasserts(flag < FlagCount, stmt, "invalid flag");
    fasserts(_flags[flag] > 0, stmt, "no flags");
    _flags[flag]--;
}

void VirtualMachine::begin(Statement*) {
    _memory.push_back(new StackFrame());
}

void VirtualMachine::end(Statement*) {
    if (_memory.size() == 1 && _debugger) {
        _debugger->onEndProgram();
    }
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

