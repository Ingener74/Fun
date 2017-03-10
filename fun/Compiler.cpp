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
    write(Instruction::OperationCode::Push);
    write(Terminal::Type::Boolean);
    write(boolean_->value);
}

void Compiler::visit(Integer* integer_){
    write(Instruction::OperationCode::Push);
    write(Terminal::Type::Integer);
    write(integer_->value);
}

void Compiler::visit(Nil* nil_){
    write(Instruction::OperationCode::Push);
    write(Terminal::Type::Nil);
}

void Compiler::visit(Real* real_){
    write(Instruction::OperationCode::Push);
    write(Terminal::Type::Real);
    write(real_->value);
}

void Compiler::visit(String* string_){
    write(Instruction::OperationCode::Push);
    write(Terminal::Type::String);
    writeString(string_->value);
}

void Compiler::visit(AddFrame* addframe_){
}

void Compiler::visit(RemoveFrame* removeframe_){
}

void Compiler::visit(Jump* jump_){
}

void Compiler::visit(ConditionJump* conditionjump_){
}

const ByteCodeProgram& fun::Compiler::getProgram() const {
    return _program;
}

void Compiler::write(void* data, size_t size) {
    if (!_programPtr) {
        _program.clear();
        _program.resize(PROGRAM_SIZE_INCREMENT);
    }
    if ((_program.data() - _programPtr) + size > _program.size()) {
        ptrdiff_t offset = _programPtr - _program.data();
        _program.resize(_program.size() + PROGRAM_SIZE_INCREMENT);
        _programPtr = _program.data() + offset;
    }
    memcpy(_programPtr, data, size);
    _programPtr += size;
}

void Compiler::writeString(const std::string& str) {
    write(const_cast<char*>(str.data()), str.size() + 1);
}

}
