#include <iostream>
#include "Nodes.h"
#include "Utils.h"
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

void Interpreter::iterateElseIfs(ElseIf* elseifs) {
    auto elseif = elseifs;
    while (elseif)
        elseif = elseif->accept(this)->nextElseIf;
}

Interpreter::Interpreter() {
}

Interpreter::~Interpreter() {
}

void Interpreter::visit(Break* break_stmt) {
}

void Interpreter::visit(Continue* continue_stmt) {
}

void Interpreter::visit(For* for_stmt) {
}

void Interpreter::visit(Function* function) {
}

void Interpreter::visit(If* if_stmt) {
    operation = Load;
    if_stmt->cond->accept(this);
    if (operands.back()->toBoolean()) {
        iterateStatements(if_stmt->stmts);
    }
}

void Interpreter::visit(ElseIf* elseif_stmt) {
    operation = Load;
    elseif_stmt->cond->accept(this);
    if (operands.back()->toBoolean()) {
        iterateStatements(elseif_stmt->stmts);
    }
}

void Interpreter::visit(Else* else_stmt) {
    iterateStatements(else_stmt->stmts);
}

void Interpreter::visit(IfElseIfsElse* ifelseifselse_stmt) {
    ifelseifselse_stmt->ifStmts->accept(this);
    if (!operands.back()->toBoolean()) {

        auto elseif = ifelseifselse_stmt->elseIfsStmts;
        while (elseif) {
            operands.pop_back();

            elseif->accept(this);

            if (operands.back()->toBoolean()) {
                operands.pop_back();
                return;
            }

            elseif = elseif->nextElseIf;
        }
        if (auto else_stmt = ifelseifselse_stmt->elseStmts) {
            operands.pop_back();
            else_stmt->accept(this);
        }
    }
}

void Interpreter::visit(Import* import_stmt) {
}

void Interpreter::visit(Print* print) {
    operation = Load;
    print->expression->accept(this);
    cout << operands.back()->toString() << endl;
    operation = Undefined;
}

void Interpreter::visit(Return* return_stmt) {
}

void Interpreter::visit(While* while_stmt) {
}

void Interpreter::visit(Class* class_stmt) {
}

void Interpreter::visit(Exception* exception_stmt) {
}

void Interpreter::visit(Throw* throw_stmt) {
}

void Interpreter::visit(Assign* assign) {
    auto balance = operands.size();
    auto lhs = assign->ids;
    auto rhs = assign->exprs;
    while (lhs && rhs) {
        operation = Load;
        rhs = rhs->accept(this)->nextExpression;

        operation = Store;
        lhs = lhs->accept(this)->nextExpression;
    }
    fassert(balance == operands.size(), "assign balance broken");
    operation = Undefined;
}

void Interpreter::visit(BinaryOp* bin_op) {
    operation = Load;

    bin_op->lhs->accept(this);
    auto lhs = operands.back();
    operands.pop_back();

    if (lhs->getType() != operands.back()->getType()) {
    }

    bin_op->rhs->accept(this);
    auto rhs = operands.back();
    operands.pop_back();

    auto res = operate(lhs, bin_op->m_operation, rhs);

    operands.push_back(res);
}

void Interpreter::visit(Call* call) {
}

void Interpreter::visit(Dictionary* dict) {
}

void Interpreter::visit(Id* id) {
    if (operation == Load) {
        auto var = variables.find(id->value);
        fassert((var != variables.end()), (id->value + " undefined"))
        operands.push_back(var->second.second);
    } else if (operation == Store) {
        auto var = variables.find(id->value);
        if (var == variables.end()) {
            fassert(variables.insert( { id->value, { 1, operands.back() } }).second, "can't insert variable");
        } else {
            var->second = {1, operands.back()};
        }
        operands.pop_back();
    }
}

void Interpreter::visit(RoundBrackets* round_brackets) {
    round_brackets->expr->accept(this);
}

// Terminals

void Interpreter::visit(Boolean* boolean) {
    if (operation == Load)
        operands.push_back(boolean);
}

void Interpreter::visit(Integer* integer) {
    if (operation == Load)
        operands.push_back(integer);
}

void Interpreter::visit(Nil* nil) {
    if (operation == Load)
        operands.push_back(nil);
}

void Interpreter::visit(Real* real) {
    if (operation == Load)
        operands.push_back(real);
}

void Interpreter::visit(String* str) {
    if (operation == Load)
        operands.push_back(str);
}

Terminal* Interpreter::operate(Terminal* a, BinaryOp::Op op, Terminal* b) {
    if(a->getType() != b->getType()){
    }
    switch (a->getType()) {
    case Terminal::Integer: {

        auto lhs = a->toInteger();
        auto rhs = b->toInteger();

        switch (op) {
        case BinaryOp::ADD: { auto res = create<Integer>(lhs + rhs); return res; }
        case BinaryOp::SUB: { auto res = create<Integer>(lhs - rhs); return res; }
        case BinaryOp::MUL: { auto res = create<Integer>(lhs * rhs); return res; }
        case BinaryOp::DIV: { auto res = create<Integer>(lhs / rhs); return res; }
        case BinaryOp::MOD: { auto res = create<Integer>(lhs % rhs); return res; }

        case BinaryOp::EQUAL:      { auto res = create<Boolean>(lhs == rhs); return res; }
        case BinaryOp::NOT_EQUAL:  { auto res = create<Boolean>(lhs != rhs); return res; }
        case BinaryOp::MORE:       { auto res = create<Boolean>(lhs >  rhs); return res; }
        case BinaryOp::MORE_EQUAL: { auto res = create<Boolean>(lhs >= rhs); return res; }
        case BinaryOp::LESS:       { auto res = create<Boolean>(lhs <  rhs); return res; }
        case BinaryOp::LESS_EQUAL: { auto res = create<Boolean>(lhs <= rhs); return res; }
        default:
            fassert(false, "unsupported operation");
        }
    }
    case Terminal::Real: {
        auto lhs = a->toReal();
        auto rhs = b->toReal();

        switch (op) {
        case BinaryOp::ADD: { auto res = create<Real>(lhs + rhs); return res; }
        case BinaryOp::SUB: { auto res = create<Real>(lhs - rhs); return res; }
        case BinaryOp::MUL: { auto res = create<Real>(lhs * rhs); return res; }
        case BinaryOp::DIV: { auto res = create<Real>(lhs / rhs); return res; }

        case BinaryOp::EQUAL:      { auto res = create<Boolean>(lhs == rhs); return res; }
        case BinaryOp::NOT_EQUAL:  { auto res = create<Boolean>(lhs != rhs); return res; }
        case BinaryOp::MORE:       { auto res = create<Boolean>(lhs >  rhs); return res; }
        case BinaryOp::MORE_EQUAL: { auto res = create<Boolean>(lhs >= rhs); return res; }
        case BinaryOp::LESS:       { auto res = create<Boolean>(lhs <  rhs); return res; }
        case BinaryOp::LESS_EQUAL: { auto res = create<Boolean>(lhs <= rhs); return res; }
        default:
            fassert(false, "unsupported operation");
        }
    }
    case Terminal::String: {
        auto lhs = a->toString();
        auto rhs = b->toString();

        switch (op) {
        case BinaryOp::ADD: { auto res = create<String>(lhs + rhs); return res; }

        case BinaryOp::EQUAL:      { auto res = create<Boolean>(lhs == rhs); return res; }
        case BinaryOp::NOT_EQUAL:  { auto res = create<Boolean>(lhs != rhs); return res; }
        default:
            fassert(false, "unsupported operation");
        }
    }
    case Terminal::Boolean:{
        auto lhs = a->toBoolean();
        auto rhs = b->toBoolean();

        switch (op) {
        case BinaryOp::EQUAL:      { auto res = create<Boolean>(lhs == rhs); return res; }
        case BinaryOp::NOT_EQUAL:  { auto res = create<Boolean>(lhs != rhs); return res; }
        default:
            fassert(false, "unsupported operation");
        }
    }
    default:
        fassert(false, "unsupported type");
    }
}

}
