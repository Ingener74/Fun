#include <iostream>
#include "Nodes.h"
#include "Interpreter.h"

namespace fun {

using namespace std;

void Interpreter::iterateStatements(Statement* stmts) {
    while (stmts)
        stmts = stmts->accept(this)->nextStatement;
}

void Interpreter::iterateExpressions(Expression* exprs) {
}

void Interpreter::iterateIds(Id* ids) {
}

void Interpreter::iterateFunctions(Function* functions) {
}

void Interpreter::iterateAssigns(Assign* assigns) {
}

Interpreter::Interpreter() {
}

Interpreter::~Interpreter() {
}

void Interpreter::visit(Statement*) {
}

void Interpreter::visit(Break*) {
}

void Interpreter::visit(Continue*) {
}

void Interpreter::visit(For*) {
}

void Interpreter::visit(Function*) {
}

void Interpreter::visit(If*) {
}

void Interpreter::visit(ElseIf*) {
}

void Interpreter::visit(Else*) {
}

void Interpreter::visit(IfElseIfsElse*) {
}

void Interpreter::visit(Import*) {
}

void Interpreter::visit(Print* print) {
    print->expression->accept(this);
    cout << _terminals.back()->toString() << endl;
}

void Interpreter::visit(Return*) {
}

void Interpreter::visit(While*) {
}

void Interpreter::visit(Class*) {
}

void Interpreter::visit(Exception*) {
}

void Interpreter::visit(Throw*) {
}

void Interpreter::visit(Expression*) {
}

void Interpreter::visit(Assign*) {
}

void Interpreter::visit(BinaryOp*) {
}

void Interpreter::visit(Call*) {
}

void Interpreter::visit(Dictionary*) {
}

void Interpreter::visit(Id*) {
}

void Interpreter::visit(RoundBrackets*) {
}

// Terminals

void Interpreter::visit(Boolean* boolean) {
    _terminals.push_back(boolean);
}

void Interpreter::visit(Integer* integer) {
    _terminals.push_back(integer);
}

void Interpreter::visit(Nil* nil) {
    _terminals.push_back(nil);
}

void Interpreter::visit(Real* real) {
    _terminals.push_back(real);
}

void Interpreter::visit(String* str) {
    _terminals.push_back(str);
}

}
