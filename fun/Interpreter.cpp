#include <iostream>
#include <algorithm>
#include <Poco/AutoPtr.h>
#include "AST.h"
#include "Utils.h"
#include "Interpreter.h"

namespace fun {

using namespace std;
using namespace Poco;

void Interpreter::iterateStatements(Statement *stmts) {
    while (stmts)
        stmts = debug(stmts)->accept(this)->nextStatement;
}

Interpreter::Interpreter(Debugger* debugger) :
        debugger(debugger) {
    variables.push_back(unordered_map<string, AutoPtr<Terminal>>{});
}

Interpreter::~Interpreter() {
}

void Interpreter::visit(Break* break_stmt) {
    auto ops = operands.size();
    break_flag = true;
    fassertl(operands.size() == ops, break_stmt->loc, "operands balance broken after statement")
}

void Interpreter::visit(Continue* continue_stmt) {
    auto ops = operands.size();
    continue_flag = true;
    fassertl(operands.size() == ops, continue_stmt->loc, "operands balance broken after statement")
}

void Interpreter::visit(For* for_stmt) {
    auto ops = operands.size();

    fassertl(for_stmt->initial, for_stmt->loc, "for must have initial expression")
    load = true;
    debug(for_stmt->initial)->accept(this);
    load = false;

    while (true) {
        fassertl(for_stmt->condition, for_stmt->loc, "for must have condition expression")
        load = true;
        debug(for_stmt->condition)->accept(this);
        load = false;

        if (operands.back()->toBoolean()) {
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
            fassertl(for_stmt->increment, for_stmt->loc, "for must have increment expression")
            debug(for_stmt->increment)->accept(this);
        } else {
            operands.pop_back();
            break;
        }
    }

    fassertl(operands.size() == ops, for_stmt->loc, "operands balance broken after statement")
}

void Interpreter::visit(Function *function) {
    if (load || function->name) {
        operands.emplace_back(function, true);
    }

    if (function->name) {
        store = true;
        debug(function->name)->accept(this);
        store = false;
    }
}

void Interpreter::visit(Ifs *ifs_stmt) {
    auto if_stmt = ifs_stmt->if_stmts;
    while(if_stmt){
        if_stmt = if_stmt->accept(this)->nextIf;
        if(break_flag){
            break_flag = false;
            break;
        }
    }
}

void Interpreter::visit(If* if_stmt) {
    auto ops = operands.size();

    if (if_stmt->cond){
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

            break_flag = true;
        } else {
            operands.pop_back();
        }
    } else {
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

        break_flag = true;
    }
    fassertl(operands.size() == ops, if_stmt->loc, "operands balance broken after statement");
}

void Interpreter::visit(Import* import_stmt) {
    auto ops = operands.size();
    fassertl(operands.size() == ops, import_stmt->loc, "operands balance broken after statement")
}

void Interpreter::visit(Print* print) {
    auto ops = operands.size();

    load = true;
    debug(print->expression)->accept(this);
    load = false;
    cout << operands.back()->toString() << endl;

//    operands.back()->release();
    operands.pop_back();

    fassertl(operands.size() == ops, print->loc, "operands balance broken after statement")
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
    auto ops = operands.size();
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
    fassertl(operands.size() == ops, while_stmt->loc, "operands balance broken after statement")
}

void Interpreter::visit(Class* class_stmt) {
}

void Interpreter::visit(Exception* exception_stmt) {
}

void Interpreter::visit(Throw* throw_stmt) {
}

void Interpreter::visit(Assign* assign) {
    bool load_f = load;

    auto balance = operands.size();
    auto lhs = assign->ids;
    auto rhs = assign->exprs;

    while (rhs) {
        load = true;
        rhs = debug(rhs)->accept(this)->nextExpression;
        load = false;

        auto operands_diff = operands.size() - balance;

        vector<AutoPtr<Terminal>> tmp;

        for (decltype(operands_diff) i = 0; i < operands_diff; ++i) {
            tmp.push_back(operands.at(balance + i));
        }
        for (decltype(operands_diff) i = 0; i < operands_diff; ++i) {
            operands.pop_back();
        }
        for (decltype(operands_diff) i = 0; i < operands_diff; ++i) {
            if (lhs) {
                if (assign->type == BinaryOperation::NOP) {
                    operands.push_back(tmp.at(i));

                    store = true;
                    lhs = debug(lhs)->accept(this)->nextExpression;
                    store = false;
                } else {
                    load = true;
                    lhs = debug(lhs)->accept(this);
                    load = false;

                    fassertl(!operands.empty(), assign->loc, "not enogth operands")

                    AutoPtr<Terminal> L = operands.back();
                    operands.pop_back();

                    operands.push_back(tmp.at(i));

                    fassertl(!operands.empty(), assign->loc, "not enogth operands")

                    AutoPtr<Terminal> R = operands.back();
                    operands.pop_back();

                    operands.push_back(operate(L, assign->type, R));

                    store = true;
                    lhs = debug(lhs)->accept(this)->nextExpression;
                    store = false;
                }
            }
        }
    }
    while (lhs) {
        if (assign->type == BinaryOperation::NOP) {
            operands.push_back(new Nil);

            store = true;
            lhs = debug(lhs)->accept(this)->nextExpression;
            store = false;
        } else {
            load = true;
            lhs = debug(lhs)->accept(this);
            load = false;

            fassertl(!operands.empty(), assign->loc, "not enogth operands")

            AutoPtr<Terminal> L = operands.back();
            operands.pop_back();

            operands.push_back(new Nil);

            fassertl(!operands.empty(), assign->loc, "not enogth operands")

            AutoPtr<Terminal> R = operands.back();
            operands.pop_back();

            operands.push_back(operate(L, assign->type, R));

            store = true;
            lhs = debug(lhs)->accept(this)->nextExpression;
            store = false;
        }
    }

    if (load_f) {
        auto lhs = assign->ids;
        while (lhs) {
            load = true;
            lhs = debug(lhs)->accept(this)->nextExpression;
            load = false;
        }
    } else {
        // assign maybe statement
        fassertl(operands.empty(), assign->loc, "operands not empty after statement")
    }
}

void Interpreter::visit(BinaryOp* bin_op) {
    auto ops = operands.size();

    load = true;
    debug(bin_op->lhs)->accept(this);
    load = false;

    fassertl(!operands.empty(), bin_op->loc, "not enogth operands")

    AutoPtr<Terminal> lhs = operands.back();
    operands.pop_back();

    load = true;
    debug(bin_op->rhs)->accept(this);
    load = false;

    fassertl(!operands.empty(), bin_op->loc, "not enogth operands")

    AutoPtr<Terminal> rhs = operands.back();
    operands.pop_back();

    operands.push_back(operate(lhs, bin_op->m_operation, rhs));

    fassertl(operands.size() == (ops + 1), bin_op->loc, "operands balance broken after statement")
}

void Interpreter::visit(Dot *dot) {
}

void Interpreter::visit(Call* call) {
    load = true;
    debug(call->callable)->accept(this);
    load = false;

    /*
     * Get callable object
     */
    fassertl(operands.size() > 0, call->loc, "callable not found");
    fassertl(operands.back()->getType() == Terminal::Function, call->loc, "must be callable");
    auto function = operands.back().cast<Function>();
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
        stmt = debug(stmt)->accept(this)->nextStatement;
        if (return_flag) {
            return_flag = false;
            break;
        }
    }
}

void Interpreter::visit(Dictionary* dict) {
}

void Interpreter::visit(Id* id) {
    if (load) {
        for (auto it = variables.rbegin(); it != variables.rend(); ++it) {
            auto var = it->find(id->value);
            if (var == it->end()) {
                continue;
            } else {
                operands.push_back(var->second);
                fassertl(!operands.empty(), id->loc, "operands empty after expression")
                return;
            }
        }
        fassertl(false, id->loc, id->value + " undefined");
    } else if (store) {
        fassertl(operands.size() > 0, id->loc, "have no operands");

        auto rit = variables.rbegin();

        auto var = rit->find(id->value);

        auto val = operands.back();
        operands.pop_back();

        if (var == rit->end()) {
            auto it = rit->insert({id->value, val});
            fassertl(it.second, id->loc, "can't store top operands value in " + id->value);
        } else {
            var->second = val;
        }
    }
}

void Interpreter::visit(RoundBrackets* round_brackets) {
    if (round_brackets->expr){
        debug(round_brackets->expr)->accept(this);
        fassertl(!operands.empty(), round_brackets->loc, "operands empty after expression")
    }
}

// Terminals

void Interpreter::visit(Boolean *boolean) {
    if (load) {
        operands.emplace_back(boolean, true);
        fassertl(!operands.empty(), boolean->loc, "operands empty after expression")
    }
    fassertl(!store, boolean->loc, "you can't assign to value")
}

void Interpreter::visit(Integer *integer) {
    if (load) {
        operands.emplace_back(integer, true);
        fassertl(!operands.empty(), integer->loc, "operands empty after expression")
    }
    fassertl(!store, integer->loc, "you can't assign to value")
}

void Interpreter::visit(Nil *nil) {
    if (load) {
        operands.emplace_back(nil, true);
        fassertl(!operands.empty(), nil->loc, "operands empty after expression")
    }
    fassertl(!store, nil->loc, "you can't assign to value")
}

void Interpreter::visit(Real *real) {
    if (load) {
        operands.emplace_back(real, true);
        fassertl(!operands.empty(), real->loc, "operands empty after expression")
    }
    fassertl(!store, real->loc, "you can't assign to value")
}

void Interpreter::visit(String *str) {
    if (load) {
        operands.emplace_back(str, true);
        fassertl(!operands.empty(), str->loc, "operands empty after expression")
    }
    fassertl(!store, str->loc, "you can't assign to value")
}

Terminal* Interpreter::operate(Terminal* a, BinaryOperation op, Terminal* b) {
    auto seniorType = Terminal::getSeniorBinaryOpType(a, b);
    switch (seniorType) {
    case Terminal::Integer: {

        auto lhs = a->toInteger();
        auto rhs = b->toInteger();

        switch (op) {
        case BinaryOperation::ADD: { return new Integer(lhs + rhs); }
        case BinaryOperation::SUB: { return new Integer(lhs - rhs); }
        case BinaryOperation::MUL: { return new Integer(lhs * rhs); }
        case BinaryOperation::DIV: { fassert(rhs != 0, "divide by zero"); return new Integer(lhs / rhs); }
        case BinaryOperation::MOD: { fassert(rhs != 0, "divide by zero"); return new Integer(lhs % rhs); }

        case BinaryOperation::LSHIFT:     { return new Integer(lhs << rhs); }
        case BinaryOperation::RSHIFT:     { return new Integer(lhs >> rhs); }
        case BinaryOperation::BINARY_OR:  { return new Integer(lhs | rhs); }
        case BinaryOperation::BINARY_AND: { return new Integer(lhs & rhs); }
        case BinaryOperation::BINARY_XOR: { return new Integer(lhs ^ rhs); }

        case BinaryOperation::LOGIC_OR:  { return new Boolean(lhs || rhs); }
        case BinaryOperation::LOGIC_AND: { return new Boolean(lhs && rhs); }

        case BinaryOperation::EQUAL:      { return new Boolean(lhs == rhs); }
        case BinaryOperation::NOT_EQUAL:  { return new Boolean(lhs != rhs); }
        case BinaryOperation::MORE:       { return new Boolean(lhs >  rhs); }
        case BinaryOperation::MORE_EQUAL: { return new Boolean(lhs >= rhs); }
        case BinaryOperation::LESS:       { return new Boolean(lhs <  rhs); }
        case BinaryOperation::LESS_EQUAL: { return new Boolean(lhs <= rhs); }
        default:
            fassertl(false, a->loc + b->loc, "unsupported operation");
        }
        break;
    }
    case Terminal::Real: {
        auto lhs = a->toReal();
        auto rhs = b->toReal();

        switch (op) {
        case BinaryOperation::ADD: { return new Real(lhs + rhs); }
        case BinaryOperation::SUB: { return new Real(lhs - rhs); }
        case BinaryOperation::MUL: { return new Real(lhs * rhs); }
        case BinaryOperation::DIV: { fassert(rhs != 0.0, "devide by zero"); return new Real(lhs / rhs); }

        case BinaryOperation::LOGIC_OR:  { return new Boolean(Real::isTrue(lhs) || Real::isTrue(rhs)); }
        case BinaryOperation::LOGIC_AND: { return new Boolean(Real::isTrue(lhs) && Real::isTrue(rhs)); }

        case BinaryOperation::EQUAL:      { return new Boolean(lhs == rhs); }
        case BinaryOperation::NOT_EQUAL:  { return new Boolean(lhs != rhs); }
        case BinaryOperation::MORE:       { return new Boolean(lhs >  rhs); }
        case BinaryOperation::MORE_EQUAL: { return new Boolean(lhs >= rhs); }
        case BinaryOperation::LESS:       { return new Boolean(lhs <  rhs); }
        case BinaryOperation::LESS_EQUAL: { return new Boolean(lhs <= rhs); }
        default:
            fassertl(false, a->loc + b->loc, "unsupported operation");
        }
        break;
    }
    case Terminal::String: {
        auto lhs = a->toString();
        auto rhs = b->toString();

        switch (op) {
        case BinaryOperation::ADD: { return new String(lhs + rhs); }

        case BinaryOperation::LOGIC_OR:  { return new Boolean(String::isTrue(lhs) || String::isTrue(rhs)); }
        case BinaryOperation::LOGIC_AND: { return new Boolean(String::isTrue(lhs) && String::isTrue(rhs)); }

        case BinaryOperation::LSHIFT:     { return new String(lhs + rhs); }
        case BinaryOperation::RSHIFT:     { return new String(lhs + rhs); }

        case BinaryOperation::MORE:       { return new Boolean(lhs.size() >  rhs.size()); }
        case BinaryOperation::MORE_EQUAL: { return new Boolean(lhs.size() >= rhs.size()); }
        case BinaryOperation::LESS:       { return new Boolean(lhs.size() <  rhs.size()); }
        case BinaryOperation::LESS_EQUAL: { return new Boolean(lhs.size() <= rhs.size()); }

        case BinaryOperation::EQUAL:      { return new Boolean(lhs == rhs); }
        case BinaryOperation::NOT_EQUAL:  { return new Boolean(lhs != rhs); }
        default:
            fassertl(false, a->loc + b->loc, "unsupported operation");
        }
        break;
    }
    case Terminal::Boolean:{
        auto lhs = a->toBoolean();
        auto rhs = b->toBoolean();

        switch (op) {
        case BinaryOperation::MORE:       { return new Boolean(lhs >  rhs); }
        case BinaryOperation::MORE_EQUAL: { return new Boolean(lhs >= rhs); }
        case BinaryOperation::LESS:       { return new Boolean(lhs <  rhs); }
        case BinaryOperation::LESS_EQUAL: { return new Boolean(lhs <= rhs); }

        case BinaryOperation::EQUAL:      { return new Boolean(lhs == rhs); }
        case BinaryOperation::NOT_EQUAL:  { return new Boolean(lhs != rhs); }

        case BinaryOperation::LOGIC_OR:  { return new Boolean(lhs || rhs); }
        case BinaryOperation::LOGIC_AND: { return new Boolean(lhs && rhs); }

        default:
            fassertl(false, a->loc + b->loc, "unsupported operation");
        }
        break;
    }
    case Terminal::Nil: {
        switch (op) {
        case BinaryOperation::LOGIC_AND: { return new Boolean(false); }
        case BinaryOperation::LOGIC_OR: { return new Boolean(false); }

        case BinaryOperation::EQUAL:      { return new Boolean(true); }
        case BinaryOperation::NOT_EQUAL:  { return new Boolean(false); }

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

const vector<AutoPtr<Terminal>>& Interpreter::getOperands() const {
    return operands;
}

vector<AutoPtr<Terminal> >& Interpreter::getOperands() {
    return operands;
}

const vector<unordered_map<string, AutoPtr<Terminal>>>& Interpreter::getMemory() const {
    return variables;
}

vector<unordered_map<string, AutoPtr<Terminal>>>& Interpreter::getMemory() {
    return variables;
}

}
