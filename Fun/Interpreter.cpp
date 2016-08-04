#include <iostream>
#include "Nodes.h"
#include "Utils.h"
#include "Interpreter.h"

namespace fun {

using namespace std;

void Interpreter::iterateStatements(Statement* stmts) {
    while (stmts) {
        if(debugger)
            debugger->onBeforeStep();
        stmts = stmts->accept(this)->nextStatement;
    }
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

Interpreter::Interpreter(Debugger* debugger) :
        debugger(debugger) {
}

Interpreter::~Interpreter() {
}

void Interpreter::visit(Break* break_stmt) {
    break_flag = true;
}

void Interpreter::visit(Continue* continue_stmt) {
    continue_flag = true;
}

void Interpreter::visit(For* for_stmt) {
    fassert(for_stmt->initial, "for must have initial expression")
    load_flag = true;
    for_stmt->initial->accept(this);
    load_flag = false;

    while (true) {
        fassert(for_stmt->condition, "for must have condition expression")
        load_flag = true;
        for_stmt->condition->accept(this);
        load_flag = false;

        if (operands.back()->toBoolean()) {
            operands.pop_back();

            auto stmt = for_stmt->stmts;

            while (stmt) {
                if (break_flag) break;
                if (continue_flag) break;

                stmt = stmt->accept(this)->nextStatement;
            }
            if (continue_flag) {
                continue_flag = false;
                continue;
            }
            if (break_flag) {
                break_flag = false;
                break;
            }
            fassert(for_stmt->increment, "for must have increment expression")
            for_stmt->increment->accept(this);
        } else {
            operands.pop_back();
            break;
        }
    }
}

void Interpreter::visit(Function* function) {
    fassert(functions.insert({ function->name->value, function }).second, "can't insert function");
}

void Interpreter::visit(If* if_stmt) {
    load_flag = true;
    if_stmt->cond->accept(this);
    load_flag = false;

    if (operands.back()->toBoolean()) {
        operands.pop_back();

        auto stmt = if_stmt->stmts;

        while (stmt) {
            if (break_flag) {
                break_flag = false;
                break;
            }
            if (continue_flag) {
                continue_flag = false;
                break;
            }
            stmt = stmt->accept(this)->nextStatement;
        }
    }
}

void Interpreter::visit(ElseIf* elseif_stmt) {
    load_flag = true;
    elseif_stmt->cond->accept(this);
    load_flag = false;
    if (operands.back()->toBoolean()) {
        operands.pop_back();

        auto stmt = elseif_stmt->stmts;

        while (stmt) {
            if (break_flag) {
                break_flag = false;
                break;
            }
            if (continue_flag) {
                continue_flag = false;
                break;
            }
            stmt = stmt->accept(this)->nextStatement;
        }
    }
}

void Interpreter::visit(Else* else_stmt) {
    auto stmt = else_stmt->stmts;
    while (stmt) {
        if (break_flag) {
            break_flag = false;
            break;
        }
        if (continue_flag) {
            continue_flag = false;
            break;
        }
        stmt = stmt->accept(this)->nextStatement;
    }
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
    load_flag = true;
    print->expression->accept(this);
    load_flag = false;
    cout << operands.back()->toString() << endl;
//    operands.pop_back();
}

void Interpreter::visit(Return* return_stmt) {
}

void Interpreter::visit(While* while_stmt) {
    while (true) {
        load_flag = true;
        while_stmt->cond->accept(this);
        load_flag = false;

        if (operands.back()->toBoolean()) {
            operands.pop_back();

            auto stmt = while_stmt->stmts;
            while (stmt) {
                if (break_flag) break;
                if (continue_flag) break;
                stmt = stmt->accept(this)->nextStatement;
            }
            if (continue_flag) {
                continue_flag = false;
                continue;
            }
            if (break_flag) {
                break_flag = false;
                break;
            }
        } else {
            operands.pop_back();
            break;
        }
    }
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
        if (assign->type == Assign::ASSIGN) {
            load_flag = true;
            rhs = rhs->accept(this)->nextExpression;
            load_flag = false;

            store_flag = true;
            lhs = lhs->accept(this)->nextExpression;
            store_flag = false;
        } else {
            load_flag = true;
            lhs = lhs->accept(this)->nextExpression;
            load_flag = false;

            load_flag = true;
            rhs = rhs->accept(this)->nextExpression;
            load_flag = false;

            store_flag = true;
            lhs = lhs->accept(this)->nextExpression;
            store_flag = false;
        }
    }
    fassert(balance == operands.size(), "assign balance broken");
}

void Interpreter::visit(BinaryOp* bin_op) {
    fassert(operands.size() >= 2, "operand is not enough " + to_<string>(operands.size()) + ", 2 expected");

    load_flag = true;
    bin_op->lhs->accept(this);
    load_flag = false;
    auto lhs = operands.back();
    operands.pop_back();

    load_flag = true;
    bin_op->rhs->accept(this);
    load_flag = false;
    auto rhs = operands.back();
    operands.pop_back();

    operands.push_back(operate(lhs, bin_op->m_operation, rhs));
}

void Interpreter::visit(Call* call) {
}

void Interpreter::visit(Dictionary* dict) {
}

void Interpreter::visit(Id* id) {
    if (load_flag) {
        auto var = variables.find(id->value);
        fassert((var != variables.end()), (id->value + " undefined"))
        operands.push_back(var->second.second);
    } else if (store_flag) {
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
    if (round_brackets->expr)
        round_brackets->expr->accept(this);
}

// Terminals

void Interpreter::visit(Boolean* boolean) {
    if (load_flag)
        operands.push_back(boolean);
    fassert(!store_flag, "you can't assign to value")
}

void Interpreter::visit(Integer* integer) {
    if (load_flag)
        operands.push_back(integer);
    fassert(!store_flag, "you can't assign to value")
}

void Interpreter::visit(Nil* nil) {
    if (load_flag)
        operands.push_back(nil);
    fassert(!store_flag, "you can't assign to value")
}

void Interpreter::visit(Real* real) {
    if (load_flag)
        operands.push_back(real);
    fassert(!store_flag, "you can't assign to value")
}

void Interpreter::visit(String* str) {
    if (load_flag)
        operands.push_back(str);
    fassert(!store_flag, "you can't assign to value")
}

Terminal* Interpreter::operate(Terminal* a, BinaryOp::Op op, Terminal* b) {
    switch (a->getType()) {
    case Terminal::Integer: {

        auto lhs = a->toInteger();
        auto rhs = b->toInteger();

        switch (op) {
        case BinaryOp::ADD: { return create<Integer>(lhs + rhs); }
        case BinaryOp::SUB: { return create<Integer>(lhs - rhs); }
        case BinaryOp::MUL: { return create<Integer>(lhs * rhs); }
        case BinaryOp::DIV: { return create<Integer>(lhs / rhs); }
        case BinaryOp::MOD: { return create<Integer>(lhs % rhs); }

        case BinaryOp::EQUAL:      { return create<Boolean>(lhs == rhs); }
        case BinaryOp::NOT_EQUAL:  { return create<Boolean>(lhs != rhs); }
        case BinaryOp::MORE:       { return create<Boolean>(lhs >  rhs); }
        case BinaryOp::MORE_EQUAL: { return create<Boolean>(lhs >= rhs); }
        case BinaryOp::LESS:       { return create<Boolean>(lhs <  rhs); }
        case BinaryOp::LESS_EQUAL: { return create<Boolean>(lhs <= rhs); }
        default:
            fassert(false, "unsupported operation");
        }
    }
    case Terminal::Real: {
        auto lhs = a->toReal();
        auto rhs = b->toReal();

        switch (op) {
        case BinaryOp::ADD: { return create<Real>(lhs + rhs); }
        case BinaryOp::SUB: { return create<Real>(lhs - rhs); }
        case BinaryOp::MUL: { return create<Real>(lhs * rhs); }
        case BinaryOp::DIV: { return create<Real>(lhs / rhs); }

        case BinaryOp::EQUAL:      { return create<Boolean>(lhs == rhs); }
        case BinaryOp::NOT_EQUAL:  { return create<Boolean>(lhs != rhs); }
        case BinaryOp::MORE:       { return create<Boolean>(lhs >  rhs); }
        case BinaryOp::MORE_EQUAL: { return create<Boolean>(lhs >= rhs); }
        case BinaryOp::LESS:       { return create<Boolean>(lhs <  rhs); }
        case BinaryOp::LESS_EQUAL: { return create<Boolean>(lhs <= rhs); }
        default:
            fassert(false, "unsupported operation");
        }
    }
    case Terminal::String: {
        auto lhs = a->toString();
        auto rhs = b->toString();

        switch (op) {
        case BinaryOp::ADD: { return create<String>(lhs + rhs); }

        case BinaryOp::EQUAL:      { return create<Boolean>(lhs == rhs); }
        case BinaryOp::NOT_EQUAL:  { return create<Boolean>(lhs != rhs); }
        default:
            fassert(false, "unsupported operation");
        }
    }
    case Terminal::Boolean:{
        auto lhs = a->toBoolean();
        auto rhs = b->toBoolean();

        switch (op) {
        case BinaryOp::EQUAL:      { return create<Boolean>(lhs == rhs); }
        case BinaryOp::NOT_EQUAL:  { return create<Boolean>(lhs != rhs); }
        default:
            fassert(false, "unsupported operation");
        }
    }
    default:
        fassert(false, "unsupported type");
    }
}

const Operands &Interpreter::getOperands() const {
    return operands;
}

}

const fun::Memory &fun::Interpreter::getMemory() const {
    return variables;
}
