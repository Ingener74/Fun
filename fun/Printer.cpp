#include "Printer.h"

#include <map>
#include <iostream>
#include <sstream>
#include "AST.h"
#include "Utils.h"

namespace fun {

using namespace std;

Printer::Printer() {
}

Printer::~Printer() {
}

void Printer::iterateStatements(Statement* stmt) {
    while (stmt) {
        cout << indents();
        stmt = stmt->accept(this)->nextStatement;
        cout << endl;
    }
}

void fun::Printer::iterateExpressions(Expression* expr) {
    while (expr) {
        expr = expr->accept(this)->nextExpression;
        if (expr)
            cout << ", ";
    }
}

void Printer::iterateIds(Id* id) {
    while (id) {
        id = id->accept(this)->nextId;
        if (id)
            cout << ", ";
    }
}

void Printer::iterateFunctions(Function* function) {
    while (function)
        function = function->accept(this)->nextFunction;
}

void Printer::iterateAssigns(Assign* assign) {
    while (assign) {
        cout << indents();
        assign = assign->accept(this)->nextAssign;
        cout << endl;
    }
}

// Statements

void Printer::visit(Break* break_stmt) {
    cout << "break";
}

void Printer::visit(Continue* continue_stmt) {
    cout << "continue";
}

void Printer::visit(Class* class_stmt) {
    cout << "class ";
    iterateIds(class_stmt->name);
    cout << "(";
    iterateIds(class_stmt->derived);
    cout << ")" << endl;
    _scopeLevel++;
    iterateStatements(class_stmt->stmts);
    _scopeLevel--;
    cout << indents() << "end" << endl;
}

void Printer::visit(For* for_stmt) {
    cout << "for ";
    if (for_stmt->initial)
        Expression::apply(for_stmt->initial, this);
    cout << "; ";
    if (for_stmt->condition)
        Expression::apply(for_stmt->condition, this);
    cout << "; ";
    if (for_stmt->increment)
        Expression::apply(for_stmt->increment, this);
    cout << ":" << endl;
    if (for_stmt->stmts) {
        _scopeLevel++;
        iterateStatements(for_stmt->stmts);
        _scopeLevel--;
    }
    cout << indents() << "end";
}

void Printer::visit(Function* function) {
    cout << "fun ";
    if(function->name)
        function->name->accept(this);
    cout << "(";
    if (function->args) {
        auto arg = function->args;
        while (arg) {
            arg = arg->accept(this)->nextId;
            if(arg)
                cout << ", ";
        }
    }
    cout << ")" << endl;
    if (function->stmts) {
        _scopeLevel++;
        iterateStatements(function->stmts);
        _scopeLevel--;
    }
    cout << indents() << "end";
}

void Printer::visit(Ifs *ifs_stmt) {
    auto if_stmt = ifs_stmt->if_stmts;
    while (if_stmt){
        if_stmt = if_stmt->accept(this)->nextIf;
        if(if_stmt)
            cout << indents();
    }
    cout << indents() << "end";
}

void Printer::visit(If *if_stmt) {
    if (if_stmt->cond) {
        cout << "if ";
        Expression::apply(if_stmt->cond, this);
        cout << ":" << endl;
    } else {
        cout << "else" << endl;
    }
    if (if_stmt->stmts) {
        _scopeLevel++;
        iterateStatements(if_stmt->stmts);
        _scopeLevel--;
    }
}

void Printer::visit(Import* import) {
    cout << "import ";
    if (import->id) {
        auto id = import->id;
        while (id) {
            id = id->accept(this)->nextId;
            if (id)
                cout << ", ";
        }
    }
}

void Printer::visit(Print* print) {
    cout << "print ";
    auto expr = print->expression;
    while (expr) {
        expr = expr->accept(this)->nextExpression;
        if (expr)
            cout << ", ";
    }
}

void Printer::visit(Return* return_stmt) {
    cout << "ret ";
    if (return_stmt->expression) {
        auto expr = return_stmt->expression;
        while (expr) {
            expr = expr->accept(this)->nextExpression;
            if (expr)
                cout << ", " << endl;
        }
    }
}

void Printer::visit(While* while_stmt) {
    cout << "while ";
    if (while_stmt->cond)
        Expression::apply(while_stmt->cond, this);
    cout << ":" << endl;
    if (while_stmt->stmts) {
        _scopeLevel++;
        iterateStatements(while_stmt->stmts);
        _scopeLevel--;
    }
    cout << indents() << "end";
}

void Printer::visit(Exception* exception_stmt) {
    cout << "try" << endl;
    _scopeLevel++;
    iterateStatements(exception_stmt->tryStmts);
    _scopeLevel--;
    cout << indents() << "catch ";
    iterateIds(exception_stmt->errorClasses);
    cout << " as ";
    iterateIds(exception_stmt->errorObject);
    cout << endl;
    _scopeLevel++;
    iterateStatements(exception_stmt->catchStmts);
    _scopeLevel--;
    cout << indents() << "end";
}

void Printer::visit(Throw* throw_stmt) {
    cout << "throw ";
    if (throw_stmt->expression) {
        iterateExpressions(throw_stmt->expression);
    }
}

// Expression

void Printer::visit(Assign* assign) {
    auto id = assign->ids;
    while (id) {
        id = id->accept(this)->nextExpression;
        if (id)
            cout << ", ";
    }

    static map<BinaryOperation, string> assigns{
        {BinaryOperation::Assign,      "="},
        {BinaryOperation::Add,         "+="},
        {BinaryOperation::Sub,         "-="},
        {BinaryOperation::Mul,         "*="},
        {BinaryOperation::Div,         "/="},
        {BinaryOperation::Mod,         "%="},
        {BinaryOperation::BinaryOr,    "|="},
        {BinaryOperation::BinaryAnd,   "&="},
        {BinaryOperation::BinaryXor,   "^="},
        {BinaryOperation::LShift,      "<<="},
        {BinaryOperation::RShift,      ">>="},
    };

    cout << " " << assigns[assign->type] << " ";

    auto expr = assign->exprs;
    while (expr) {
        expr = expr->accept(this)->nextExpression;
        if (expr)
            cout << ", ";
    }
}

void Printer::visit(BinaryOp* bin_op) {
    bin_op->lhs->accept(this);

    static map<BinaryOperation, string> ops{
        {BinaryOperation::Add,         "+"},
        {BinaryOperation::Sub,         "-"},
        {BinaryOperation::Mul,         "*"},
        {BinaryOperation::Div,         "/"},
        {BinaryOperation::Mod,         "%"},
        {BinaryOperation::BinaryOr,    "|"},
        {BinaryOperation::BinaryAnd,   "&"},
        {BinaryOperation::BinaryXor,   "^"},
        {BinaryOperation::LogicAnd,    "&&"},
        {BinaryOperation::LogicOr,     "||"},
        {BinaryOperation::LShift,      "<<"},
        {BinaryOperation::RShift,      ">>"},
        {BinaryOperation::Less,        "<"},
        {BinaryOperation::More,        ">"},
        {BinaryOperation::LessEqual,   "<="},
        {BinaryOperation::MoreEqual,   ">="},
        {BinaryOperation::Equal,       "=="},
        {BinaryOperation::NotEqual,    "!="},
    };
    cout << " " << ops[bin_op->m_operation] << " ";

    bin_op->rhs->accept(this);
}

void Printer::visit(Dot* dot) {
}

void Printer::visit(Call* call) {
    call->callable->accept(this);
    cout << "(";
    if (call->arguments)
        iterateExpressions(call->arguments);
    cout << ")";
}

void Printer::visit(Dictionary* dict) {
    cout << "{" << endl;
    _scopeLevel++;
    iterateAssigns(dict->assign);
    _scopeLevel--;
    cout << "}";
}

void Printer::visit(Id* node) {
    cout << node->value;
}

void Printer::visit(Index* index) {
    index->indexable->accept(this);
    cout << "[";
    index->arg->accept(this);
    cout << "]";
}

void Printer::visit(RoundBrackets* round) {
    cout << "(";
    iterateExpressions(round->expr);
    cout << ")";
}

// Terminal

void Printer::visit(Boolean* node) {
    cout << std::boolalpha << node->value;
}

void Printer::visit(Integer* node) {
    cout << node->value;
}

void Printer::visit(Nil*) {
    cout << "nil";
}

void Printer::visit(Real* node) {
    cout << node->value;
}

void Printer::visit(String* node) {
    cout << "\"" << node->value << "\"";
}

std::string Printer::indents() const {
    return [=] {
        stringstream ss;
        for(size_t i = 0; i < _scopeLevel; ++i)
            ss << "    ";
        return ss.str();
    }();
}

}
