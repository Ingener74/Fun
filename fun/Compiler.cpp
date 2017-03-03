#include "Compiler.h"

namespace fun {

Compiler::Compiler() {
}

Compiler::~Compiler() {
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
}

void Compiler::visit(Integer* integer_){
}

void Compiler::visit(Nil* nil_){
}

void Compiler::visit(Real* real_){
}

void Compiler::visit(String* string_){
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

}
