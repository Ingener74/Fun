#include <iostream>
#include <algorithm>
#include "Nodes.h"
#include "Utils.h"
#include "Interpreter.h"

namespace fun {

using namespace std;

#define RELEASE_TOP operands.back()->release(); operands.pop_back();

void Interpreter::iterateStatements(Statement *stmts) {
    while (stmts)
        stmts = debug(stmts)->accept(this)->nextStatement;
}

Interpreter::Interpreter(Debugger* debugger) :
        debugger(debugger) {
    variables.push_back(std::unordered_map<std::string, Terminal*>{});
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
            RELEASE_TOP

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
            RELEASE_TOP
            break;
        }
    }

    fassertl(operands.size() == ops, for_stmt->loc, "operands balance broken after statement")
}

void Interpreter::visit(Function *function) {
    if (load || function->name){
        operands.push_back(function);
        function->duplicate();
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
            RELEASE_TOP

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
            RELEASE_TOP
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

    operands.back()->release();
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

    fassertl(operands.empty(), assign->loc, "operands not empty after statement") // assign maybe statement
//    fassert(!operands.empty(), "operands empty after expression")
}

void Interpreter::visit(BinaryOp* bin_op) {
    auto ops = operands.size();

    load = true;
    debug(bin_op->lhs)->accept(this);
    load = false;

    fassertl(!operands.empty(), bin_op->loc, "not enogth operands")

    auto lhs = operands.back();
    operands.pop_back();

    load = true;
    debug(bin_op->rhs)->accept(this);
    load = false;

    fassertl(!operands.empty(), bin_op->loc, "not enogth operands")

    auto rhs = operands.back();
    operands.pop_back();

    operands.push_back(operate(lhs, bin_op->m_operation, rhs));

    lhs->release();
    rhs->release();

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
        stmt = debug(stmt)->accept(this)->nextStatement;
        if (return_flag) {
            return_flag = false;
            break;
        }
    }
    function->release();

//    fassert(!operands.empty(), "operands empty after expression")
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
                var->second->duplicate();
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
        operands.push_back(boolean);
        boolean->duplicate();
        fassertl(!operands.empty(), boolean->loc, "operands empty after expression")
    }
    fassertl(!store, boolean->loc, "you can't assign to value")
}

void Interpreter::visit(Integer *integer) {
    if (load) {
        operands.push_back(integer);
        integer->duplicate();
        fassertl(!operands.empty(), integer->loc, "operands empty after expression")
    }
    fassertl(!store, integer->loc, "you can't assign to value")
}

void Interpreter::visit(Nil *nil) {
    if (load) {
        operands.push_back(nil);
        nil->duplicate();
        fassertl(!operands.empty(), nil->loc, "operands empty after expression")
    }
    fassertl(!store, nil->loc, "you can't assign to value")
}

void Interpreter::visit(Real *real) {
    if (load) {
        operands.push_back(real);
        real->duplicate();
        fassertl(!operands.empty(), real->loc, "operands empty after expression")
    }
    fassertl(!store, real->loc, "you can't assign to value")
}

void Interpreter::visit(String *str) {
    if (load) {
        operands.push_back(str);
        str->duplicate();
        fassertl(!operands.empty(), str->loc, "operands empty after expression")
    }
    fassertl(!store, str->loc, "you can't assign to value")
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
            fassertl(false, a->loc + b->loc, "unsupported operation");
        }
        break;
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
            fassertl(false, a->loc + b->loc, "unsupported operation");
        }
        break;
    }
    case Terminal::String: {
        auto lhs = a->toString();
        auto rhs = b->toString();

        switch (op) {
        case BinaryOp::ADD: { return new String(lhs + rhs); }

        case BinaryOp::EQUAL:      { return new Boolean(lhs == rhs); }
        case BinaryOp::NOT_EQUAL:  { return new Boolean(lhs != rhs); }
        default:
            fassertl(false, a->loc + b->loc, "unsupported operation");

        }
        break;
    }
    case Terminal::Boolean:{
        auto lhs = a->toBoolean();
        auto rhs = b->toBoolean();

        switch (op) {
        case BinaryOp::EQUAL:      { return new Boolean(lhs == rhs); }
        case BinaryOp::NOT_EQUAL:  { return new Boolean(lhs != rhs); }
        default:
            fassertl(false, a->loc + b->loc, "unsupported operation");
        }
        break;
    }
    default:
        fassertl(false, a->loc + b->loc, "unsupported operation");
    }
}

const std::vector<Terminal*> &Interpreter::getOperands() const {
    return operands;
}

const std::vector<std::unordered_map<std::string, Terminal*>>& Interpreter::getMemory() const {
    return variables;
}

}
