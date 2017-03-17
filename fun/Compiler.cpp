#include <cstring>
#include "VirtualMachine.h"
#include "AST.h"
#include "Compiler.h"

namespace fun {

Compiler::Compiler() {
}

Compiler::~Compiler() {
}

void Compiler::iterateStatements(Statement* statement_) {
    statement_->accept(this);
    size_t realProgramSize = _programPtr - _program.data();
    _program.resize(realProgramSize);
}

void Compiler::visit(Statement* statement_){
}

void Compiler::visit(Break* break_){
}

void Compiler::visit(Continue* continue_){
}

void Compiler::visit(Class* class_){
}

void Compiler::visit(For* for_){
}

void Compiler::visit(Function* function_){
}

void Compiler::visit(Ifs* ifs_){
}

void Compiler::visit(If* if_){
}

void Compiler::visit(Import* import_){
}

void Compiler::visit(Print* print_){
}

void Compiler::visit(Return* return_){
}

void Compiler::visit(While* while_){
}

void Compiler::visit(Exception* exception_){
}

void Compiler::visit(Throw* throw_){
}

void Compiler::visit(Expression* expression_){
}

void Compiler::visit(Assign* assign_){
}

void Compiler::visit(BinaryOp* binaryop_){
    write(OpCode::SetFlag);
    write(Flag::Load);

    binaryop_->lhs->accept(this);
    binaryop_->rhs->accept(this);

    write(OpCode::ClearFlag);
    write(Flag::Load);

    write(OpCode::BinaryOperation);
    write(binaryop_->m_operation);
}

void Compiler::visit(Dot* dot_){
}

void Compiler::visit(Call* call_){
}

void Compiler::visit(Dictionary* dictionary_){
}

void Compiler::visit(Id* id_){
}

void Compiler::visit(Index* index_){
}

void Compiler::visit(RoundBrackets* roundbrackets_){
}

void Compiler::visit(Terminal* terminal_){
}

void Compiler::visit(Boolean* boolean_){
    write(OpCode::Push);
    write(Type::Boolean);
    write(boolean_->value);
}

void Compiler::visit(Integer* integer_){
    write(OpCode::Push);
    write(Type::Integer);
    write(integer_->value);
}

void Compiler::visit(Nil* nil_){
    write(OpCode::Push);
    write(Type::Nil);
}

void Compiler::visit(Real* real_){
    write(OpCode::Push);
    write(Type::Real);
    write(real_->value);
}

void Compiler::visit(String* string_){
    write(OpCode::Push);
    write(Type::String);
    write(uint32_t(string_->value.size()));
    writeString(string_->value);
}

const ByteCodeProgram& fun::Compiler::getProgram() const {
    return _program;
}

void Compiler::checkOffsetAndResizeProgram(ptrdiff_t offset) {
    if (_program.empty()) {
        _program.resize(PROGRAM_SIZE_INCREMENT);
    }
    ptrdiff_t oldOffset = 0;
    if (_programPtr) {
        oldOffset = _programPtr - _program.data();
    }
    while (offset > _program.size()) {
        _program.resize(_program.size() + PROGRAM_SIZE_INCREMENT);
    }
    if (_programPtr) {
        _programPtr = _program.data() + oldOffset;
    } else {
        _programPtr = _program.data();
    }
}

void Compiler::checkPointerAndResizeProgram(void* ptr) {
    checkOffsetAndResizeProgram(static_cast<uint8_t*>(ptr) - _program.data());
}

void Compiler::write(void* to, void* data, size_t size) {
    checkPointerAndResizeProgram(to);
    memcpy(to, data, size);
}

void Compiler::write(void* data, size_t size) {
    checkPointerAndResizeProgram(_programPtr);
    write(_programPtr, data, size);
    _programPtr += size;
}

void Compiler::writeString(const std::string& str) {
    write(const_cast<char*>(str.data()), str.size() + 1);
}

}
