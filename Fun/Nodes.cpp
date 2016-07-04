#include "Visitor.h"
#include "Utils.h"
#include "Nodes.h"

namespace fun {

using namespace std;

Statement* Statement::entryPoint = nullptr;
std::vector<std::unique_ptr<Statement>> Statement::statements;

void Statement::clear() {
    entryPoint = nullptr;
    statements.clear();
}

int Statement::apply(Visitor* v) {
    return apply(entryPoint, v);
}

int Statement::apply(Statement* start, Visitor* v) {
    if (!start)
        return -1;

    do {
        start->accept(v);
        start = start->nextStatement;
    } while (start);
    return 0;
}

void Import::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(id, "Import must have an id");
    Id::apply(id, v);
    v->visit(this);
}

void Return::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    if (expression) {
        auto curExpr = expression;
        do {
            curExpr->accept(v);
            curExpr = curExpr->nextExpression;
        } while (curExpr);
    }
    v->visit(this);
}

void Print::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(expression, "Print must have the expressions")
    auto curExpr = expression;
    do {
        curExpr->accept(v);
        curExpr = curExpr->nextExpression;
    } while (curExpr);
    v->visit(this);
}

void Function::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(name, "Function must have the name");
    name->accept(v);
    if (args)
        args->accept(v);
    if (scope)
        scope->accept(v);
    v->visit(this);
}

void If::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(condition, "If must have the condition expression");
    condition->accept(v);
    apply(thenScope, v);
    apply(elseScope, v);
    v->visit(this);
}

void While::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(condition, "While must have the condition expression");
    condition->accept(v);
    apply(scope, v);
    v->visit(this);
}

void For::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    if (initial)
        initial->accept(v);
    if (condition)
        condition->accept(v);
    if (increment)
        increment->accept(v);
    apply(scope, v);
    v->visit(this);
}

void Break::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    v->visit(this);
}

void Continue::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    v->visit(this);
}

void Expression::apply(Expression* expression, Visitor* v) {
    auto expr = expression;
    do {
        expr->accept(v);
        expr = expr->nextExpression;
    } while (expr);
}

void Id::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
}

void Id::apply(Id* id, Visitor* v) {
    auto currentId = id;
    do {
        currentId->accept(v);
        currentId = currentId->nextId;
    } while (currentId);
}

void Assign::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(name, "Assign must have name")
    name->accept(v);
    fassert(value, "Assign must have value")
    value->accept(v);
    v->visit(this);
}

void BinaryOp::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(lhs, "Binary operation must have left side expression")
    lhs->accept(v);
    fassert(rhs, "Binary operation must have right side expression")
    rhs->accept(v);
    v->visit(this);
}

void Call::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(name, "Call expression must have name")
    name->accept(v);
    Expression::apply(arguments, v);
    v->visit(this);
}

void Integer::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
}

void Real::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
}

void String::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
}

void Boolean::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
}

void Null::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
}

}

