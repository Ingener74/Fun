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

    std::string sourceFileSha256Hash;
    bool hasSourceFileHash = !sourceFileSha256Hash.empty();
    write(hasSourceFileHash);
    if (hasSourceFileHash)
        write(sourceFileSha256Hash);
    write(_debugInfo ? BuildType::Debug : BuildType::Release);

    write(OpCode::Begin, statement_);

    statement_->accept(this);

    write(OpCode::End, statement_);

    write(OpCode::SetFlag, statement_);
    write(FlagStop);

    size_t realProgramSize = _programPtr - _program.data();
    _program.resize(realProgramSize);
}

void Compiler::visit(Statement* statement_) {
    fassert(false, "invalid statement");
}

void Compiler::visit(Break* break_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(Continue* continue_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(Class* class_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(For* for_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(Function* function_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(Ifs* ifs_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(If* if_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(Import* import_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(Print* print_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(Return* return_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(While* while_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(Exception* exception_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(Throw* throw_) {
    fassert(false, "not yet implemented");
}

void Compiler::visit(Expression* expression_) {
    fassert(false, "invalid statement");
}

void Compiler::visit(Assign* assign_) {
    auto expr = assign_->exprs;
    auto id = assign_->ids;

    while (expr || id) {
        write(OpCode::SetFlag, assign_);
        write(FlagLoad);

        expr = expr->accept(this)->nextExpression;

        write(OpCode::ClearFlag, assign_);
        write(FlagLoad);

        write(OpCode::SetFlag, assign_);
        write(FlagStore);

        id = id->accept(this)->nextExpression;

        write(OpCode::ClearFlag, assign_);
        write(FlagStore);
    }
    if (expr) {
        while (expr)
            expr = expr->accept(this)->nextExpression;
    }
    if (id) {
        while (id)
            id = id->accept(this)->nextExpression;
    }
}

void Compiler::visit(BinaryOp* binaryop_) {
    write(OpCode::SetFlag, binaryop_);
    write(FlagLoad);

    binaryop_->lhs->accept(this);
    binaryop_->rhs->accept(this);

    write(OpCode::ClearFlag, binaryop_);
    write(FlagLoad);

    write(OpCode::BinaryOperation, binaryop_);
    write(binaryop_->m_operation);
}

void Compiler::visit(Dot* dot_) {
}

void Compiler::visit(Call* call_) {
}

void Compiler::visit(Dictionary* dictionary_) {
}

void Compiler::visit(Id* id_) {
    write(OpCode::Memory, id_);
    write(id_->value);
}

void Compiler::visit(Index* index_) {
}

void Compiler::visit(RoundBrackets* roundbrackets_) {
    roundbrackets_->accept(this);
}

void Compiler::visit(Terminal* terminal_) {
    fassert(false, "invalid statement");
}

void Compiler::visit(Boolean* boolean_) {
    write(OpCode::Push, boolean_);
    write(Type::Boolean);
    write(boolean_->value);
}

void Compiler::visit(Integer* integer_) {
    write(OpCode::Push, integer_);
    write(Type::Integer);
    write(integer_->value);
}

void Compiler::visit(Nil* nil_) {
    write(OpCode::Push, nil_);
    write(Type::Nil);
}

void Compiler::visit(Real* real_) {
    write(OpCode::Push, real_);
    write(Type::Real);
    write(real_->value);
}

void Compiler::visit(String* string_) {
    write(OpCode::Push, string_);
    write(Type::String);
    write(string_->value);
}

const ByteCodeProgram& fun::Compiler::getProgram() const {
    return _program;
}

void Compiler::checkOffsetAndResizeProgram(ptrdiff_t offset, size_t size) {
    while ((offset + size) > _program.size()) {
        ptrdiff_t oldOffset = _programPtr - _program.data();
        _program.resize(_program.size() + PROGRAM_SIZE_INCREMENT);
        _programPtr = _program.data() + oldOffset;
    }
}

void Compiler::checkPointerAndResizeProgram(void* ptr, size_t size) {
    checkOffsetAndResizeProgram(static_cast<uint8_t*>(ptr) - _program.data(), size);
}

void Compiler::write(void* to, void* data, size_t size) {
    checkPointerAndResizeProgram(to, size);
    memcpy(to, data, size);
}

void Compiler::write(void* data, size_t size) {
    checkPointerAndResizeProgram(_programPtr, size);
    write(_programPtr, data, size);
    _programPtr += size;
}

void Compiler::write(const std::string& str) {
    write(uint32_t(str.size()));
    write(const_cast<char*>(str.data()), str.size());
}

void Compiler::write(OpCode opcode, Statement* stmt) {
    write(&opcode, sizeof(opcode));
    if (_debugInfo)
        write(stmt->statementId);
}

template<>
inline void Compiler::write(const OpCode& data) {
    fassert(false, "invalid write use write(OpCode, Statement)");
}

}
