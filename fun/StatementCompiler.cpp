#include <vector>

#include "Utils.h"
#include "AST.h"
#include "StatementCompiler.h"

namespace fun {

StatementCompiler::StatementCompiler() {
}

StatementCompiler::~StatementCompiler() {
}

void StatementCompiler::iterateStatements(Statement* stmts) {
    stmts->accept(this);

}

void StatementCompiler::visit(Statement* statement_) {
    fassert(false, "can't compile statement");
}

void StatementCompiler::visit(Break* break_) {
}

void StatementCompiler::visit(Continue* continue_) {
}

void StatementCompiler::visit(Class* class_) {
}

void StatementCompiler::visit(For* for_) {
}

void StatementCompiler::visit(Function* function_) {
}

void StatementCompiler::visit(Ifs* ifs_) {
}

void StatementCompiler::visit(If* if_) {
}

void StatementCompiler::visit(Import* import_) {
}

void StatementCompiler::visit(Print* print_) {
}

void StatementCompiler::visit(Return* return_) {
}

void StatementCompiler::visit(While* while_) {
}

void StatementCompiler::visit(Exception* exception_) {
}

void StatementCompiler::visit(Throw* throw_) {
}

void StatementCompiler::visit(Expression* expression_) {
    fassert(false, "can't compile expression");
}

void StatementCompiler::visit(Assign* assign_) {
    _program.push_back(assign_);
}

void StatementCompiler::visit(BinaryOp* binaryop_) {
}

void StatementCompiler::visit(Dot* dot_) {
}

void StatementCompiler::visit(Call* call_) {
}

void StatementCompiler::visit(Dictionary* dictionary_) {
}

void StatementCompiler::visit(Id* id_) {
}

void StatementCompiler::visit(Index* index_) {
}

void StatementCompiler::visit(RoundBrackets* roundbrackets_) {
}

void StatementCompiler::visit(Terminal* terminal_) {
    fassert(false, "can't compile terminal");
}

void StatementCompiler::visit(Boolean* boolean_) {
}

void StatementCompiler::visit(Integer* integer_) {
}

void StatementCompiler::visit(Nil* nil_) {
}

void StatementCompiler::visit(Real* real_) {
}

void StatementCompiler::visit(String* string_) {
}

void StatementCompiler::visit(AddFrame* addframe_) {
}

void StatementCompiler::visit(RemoveFrame* removeframe_) {
}

void StatementCompiler::visit(Jump* jump_) {
}

void StatementCompiler::visit(ConditionJump* conditionjump_) {
}

const Program& StatementCompiler::getProgram() const {
    return _program;
}

}
