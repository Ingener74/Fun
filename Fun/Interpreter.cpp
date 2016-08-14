#include <iostream>
#include <algorithm>
#include "Nodes.h"
#include "Utils.h"
#include "Interpreter.h"
#include "Printer.h"

namespace fun {

using namespace std;

void Debugger::setBreakpoint(const Breakpoint &breakpoint) {
    vb.push_back(breakpoint);
}

void Debugger::enableBreakpoint(const Breakpoint &breakpoint) {
}

void Debugger::disableBreakpoint(const Breakpoint &breakpoint) {
}

void Debugger::removeBreakpoint(const Breakpoint &breakpoint) {
    auto it = find(begin(vb), end(vb), breakpoint);
    if(it == vb.end())
        return;
    vb.erase(it);
}

const Breakpoints& Debugger::getBreakpoints() const {
    return vb;
}

void Debugger::pause() {
}

void Debugger::resume() {
    _wr.run();
}

void Debugger::stepOver() {
    _wr.run();
}

void Debugger::stepIn() {
}

void Debugger::stepOut() {
}

void Debugger::onBeforeStep(Statement * s) {
    _currentStatement = s;
    _wr.wait();
}

void Debugger::list() {
    if(_currentStatement)
        _currentStatement->accept(_printer);
}

void Interpreter::iterateStatements(Statement *stmts) {
    while (stmts)
        stmts = debug(stmts)->accept(this)->nextStatement;
}

Interpreter::Interpreter(Debugger* debugger) :
        debugger(debugger) {
}

Interpreter::~Interpreter() {
}

void Interpreter::visit(Break* break_stmt) {
    break_flag = true;
    fassert(operands.empty(), "operands not empty after statement")
}

void Interpreter::visit(Continue* continue_stmt) {
    continue_flag = true;
    fassert(operands.empty(), "operands not empty after statement")
}

void Interpreter::visit(For* for_stmt) {
    fassert(for_stmt->initial, "for must have initial expression")
    load = true;
    debug(for_stmt->initial)->accept(this);
    load = false;

    while (true) {
        fassert(for_stmt->condition, "for must have condition expression")
        load = true;
        debug(for_stmt->condition)->accept(this);
        load = false;

        if (operands.back()->toBoolean()) {

            operands.back()->release();
            operands.pop_back();

            auto stmt = for_stmt->stmts;

            while (stmt) {
                if (break_flag) break;
                if (continue_flag) break;

                stmt = debug(stmt)->accept(this)->nextStatement;
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
            debug(for_stmt->increment)->accept(this);
        } else {
            operands.back()->release();
            operands.pop_back();
            break;
        }
    }

    fassert(operands.empty(), "operands not empty after statement")
}

void Interpreter::visit(Function *function) {
    if (load || function->name)
        operands.push_back(function);

    if (function->name) {
        store = true;
        debug(function->name)->accept(this);
        store = false;
    }
}

void Interpreter::visit(If* if_stmt) {

    load = true;
    debug(if_stmt->cond)->accept(this);
    load = false;

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

            stmt = debug(stmt)->accept(this)->nextStatement;
        }
    }
}

void Interpreter::visit(ElseIf* elseif_stmt) {
    load = true;
    debug(elseif_stmt->cond)->accept(this);
    load = false;
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
            stmt = debug(stmt)->accept(this)->nextStatement;
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
        stmt = debug(stmt)->accept(this)->nextStatement;
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
    fassert(operands.empty(), "operands not empty after statement")
}

void Interpreter::visit(Import* import_stmt) {
    fassert(operands.empty(), "operands not empty after statement")
}

void Interpreter::visit(Print* print) {
    load = true;
    debug(print->expression)->accept(this);
    load = false;
    cout << operands.back()->toString() << endl;

    operands.back()->release();
    operands.pop_back();

    fassert(operands.empty(), "operands not empty after statement")
}

void Interpreter::visit(Return *return_stmt) {
    auto expr = return_stmt->expression;
    while (expr) {
        load = true;
        expr = debug(expr)->accept(this)->nextExpression;
        load = false;
    }
    return_flag = true;
//    fassert(operands.empty(), "operands not empty after statement") // return is expression maybe
}

void Interpreter::visit(While* while_stmt) {
    while (true) {
        load = true;
        debug(while_stmt->cond)->accept(this);
        load = false;

        if (operands.back()->toBoolean()) {
            operands.pop_back();

            auto stmt = while_stmt->stmts;
            while (stmt) {
                if (break_flag) break;
                if (continue_flag) break;
                stmt = debug(stmt)->accept(this)->nextStatement;
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
    fassert(operands.empty(), "operands not empty after statement")
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
            load = true;
            rhs = debug(rhs)->accept(this)->nextExpression;
            load = false;

            store = true;
            lhs = debug(lhs)->accept(this)->nextExpression;
            store = false;
        } else {
            load = true;
            lhs = debug(lhs)->accept(this)->nextExpression;
            load = false;

            load = true;
            rhs = debug(rhs)->accept(this)->nextExpression;
            load = false;

            store = true;
            lhs = debug(lhs)->accept(this)->nextExpression;
            store = false;
        }
    }
//    fassert(balance == operands.size(), "assign balance broken");

    fassert(operands.empty(), "operands not empty after statement") // assign maybe statement
//    fassert(!operands.empty(), "operands empty after expression")
}

void Interpreter::visit(BinaryOp* bin_op) {
    fassert(operands.size() >= 2, "not enough operands " + to_<string>(operands.size()) + " 2 expected");

    load = true;
    debug(bin_op->lhs)->accept(this);
    load = false;
    auto lhs = operands.back();
    operands.pop_back();

    load = true;
    debug(bin_op->rhs)->accept(this);
    load = false;
    auto rhs = operands.back();
    operands.pop_back();

    operands.push_back(operate(lhs, bin_op->m_operation, rhs));

    lhs->release();
    rhs->release();

    fassert(!operands.empty(), "operands empty after expression")
}

void Interpreter::visit(Call* call) {
    load = true;
    debug(call->callable)->accept(this);
    load = false;

    /*
     * Get callable object
     */
    fassert(operands.size() > 0, "callable not found");
    fassert(operands.back()->getType() == Terminal::Function, "must be callable");
    auto function = dynamic_cast<Function*>(operands.back());
    operands.pop_back();

    /*
     * Assign passed expressions to parameters
     */
    auto expr = call->arguments;
    auto arg = function->args;
    while(expr && arg){
        load = true;
        expr = debug(expr)->accept(this)->nextExpression;
        load = false;

        store = true;
        arg = debug(arg)->accept(this)->nextId;
        store = false;
    }

    /*
     * Iterate function statements
     */
    auto stmt = function->stmts;

    while (stmt) {
        if (return_flag) {
            return_flag = false;
            break;
        }
        stmt = debug(stmt)->accept(this)->nextStatement;
        if (return_flag) {
            return_flag = false;
            break;
        }
    }

    fassert(!operands.empty(), "operands empty after expression")
}

void Interpreter::visit(Dictionary* dict) {
}

void Interpreter::visit(Id* id) {
    if (load) {
        auto var = variables.find(id->value);
        fassert(var != variables.end(), id->value + " undefined");
        operands.push_back(var->second);
        var->second->duplicate();

        fassert(!operands.empty(), "operands empty after expression")
    } else if (store) {
        fassert(operands.size() > 0, "have no operands");

        auto var = variables.find(id->value);

        auto val = operands.back();
        operands.pop_back();

        if (var == variables.end()) {
            auto it = variables.insert({id->value, val});
            fassert(it.second, "can't store top operands value in " + id->value);
        } else {
            var->second = val;
        }

        fassert(!operands.empty(), "operands empty after expression")
    }
}

void Interpreter::visit(RoundBrackets* round_brackets) {
    if (round_brackets->expr){
        debug(round_brackets->expr)->accept(this);
        fassert(!operands.empty(), "operands empty after expression")
    }
}

// Terminals

void Interpreter::visit(Boolean *boolean) {
    if (load) {
        operands.push_back(boolean);
        boolean->duplicate();
        fassert(!operands.empty(), "operands empty after expression")
    }
    fassert(!store, "you can't assign to value")
}

void Interpreter::visit(Integer *integer) {
    if (load) {
        operands.push_back(integer);
        integer->duplicate();
        fassert(!operands.empty(), "operands empty after expression")
    }
    fassert(!store, "you can't assign to value")
}

void Interpreter::visit(Nil *nil) {
    if (load) {
        operands.push_back(nil);
        nil->duplicate();
        fassert(!operands.empty(), "operands empty after expression")
    }
    fassert(!store, "you can't assign to value")
}

void Interpreter::visit(Real *real) {
    if (load) {
        operands.push_back(real);
        real->duplicate();
        fassert(!operands.empty(), "operands empty after expression")
    }
    fassert(!store, "you can't assign to value")
}

void Interpreter::visit(String *str) {
    if (load) {
        operands.push_back(str);
        str->duplicate();
        fassert(!operands.empty(), "operands empty after expression")
    }
    fassert(!store, "you can't assign to value")
}

Terminal* Interpreter::operate(Terminal* a, BinaryOp::Op op, Terminal* b) {
    switch (a->getType()) {
    case Terminal::Integer: {

        auto lhs = a->toInteger();
        auto rhs = b->toInteger();

        switch (op) {
        case BinaryOp::ADD: { return new Integer(lhs + rhs); }
        case BinaryOp::SUB: { return new Integer(lhs - rhs); }
        case BinaryOp::MUL: { return new Integer(lhs * rhs); }
        case BinaryOp::DIV: { return new Integer(lhs / rhs); }
        case BinaryOp::MOD: { return new Integer(lhs % rhs); }

        case BinaryOp::EQUAL:      { return new Boolean(lhs == rhs); }
        case BinaryOp::NOT_EQUAL:  { return new Boolean(lhs != rhs); }
        case BinaryOp::MORE:       { return new Boolean(lhs >  rhs); }
        case BinaryOp::MORE_EQUAL: { return new Boolean(lhs >= rhs); }
        case BinaryOp::LESS:       { return new Boolean(lhs <  rhs); }
        case BinaryOp::LESS_EQUAL: { return new Boolean(lhs <= rhs); }
        default:
            fassert(false, "unsupported operation");
        }
    }
    case Terminal::Real: {
        auto lhs = a->toReal();
        auto rhs = b->toReal();

        switch (op) {
        case BinaryOp::ADD: { return new Real(lhs + rhs); }
        case BinaryOp::SUB: { return new Real(lhs - rhs); }
        case BinaryOp::MUL: { return new Real(lhs * rhs); }
        case BinaryOp::DIV: { return new Real(lhs / rhs); }

        case BinaryOp::EQUAL:      { return new Boolean(lhs == rhs); }
        case BinaryOp::NOT_EQUAL:  { return new Boolean(lhs != rhs); }
        case BinaryOp::MORE:       { return new Boolean(lhs >  rhs); }
        case BinaryOp::MORE_EQUAL: { return new Boolean(lhs >= rhs); }
        case BinaryOp::LESS:       { return new Boolean(lhs <  rhs); }
        case BinaryOp::LESS_EQUAL: { return new Boolean(lhs <= rhs); }
        default:
            fassert(false, "unsupported operation");
        }
    }
    case Terminal::String: {
        auto lhs = a->toString();
        auto rhs = b->toString();

        switch (op) {
        case BinaryOp::ADD: { return new String(lhs + rhs); }

        case BinaryOp::EQUAL:      { return new Boolean(lhs == rhs); }
        case BinaryOp::NOT_EQUAL:  { return new Boolean(lhs != rhs); }
        default:
            fassert(false, "unsupported operation");
        }
    }
    case Terminal::Boolean:{
        auto lhs = a->toBoolean();
        auto rhs = b->toBoolean();

        switch (op) {
        case BinaryOp::EQUAL:      { return new Boolean(lhs == rhs); }
        case BinaryOp::NOT_EQUAL:  { return new Boolean(lhs != rhs); }
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

const Memory& Interpreter::getMemory() const {
    return variables;
}

}
