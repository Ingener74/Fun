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

void Statement::apply(Visitor* v) {
    apply(entryPoint, v);
}

void Statement::apply(Statement* start, Visitor* v) {
    while (start)
        start = start->accept(v)->nextStatement;
}

Break* Break::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    v->visit(this);
    return this;
}

Continue* Continue::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    v->visit(this);
    return this;
}

For* For::accept(Visitor* v) {
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
    return this;
}

Function* Function::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(name, "Function must have the name");
    name->accept(v);
    if (args)
        args->accept(v);
    if (scope)
        scope->accept(v);
    v->visit(this);
    return this;
}

If* If::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(condition, "If must have the condition expression");
    condition->accept(v);
    apply(thenScope, v);
    apply(elseScope, v);
    v->visit(this);
    return this;
}

Import* Import::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(id, "Import must have an id");
    Id::apply(id, v);
    v->visit(this);
    return this;
}

Print* Print::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(expression, "Print must have the expressions")
    auto curExpr = expression;
    do {
        curExpr->accept(v);
        curExpr = curExpr->nextExpression;
    } while (curExpr);
    v->visit(this);
    return this;
}

Return* Return::accept(Visitor* v) {
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
    return this;
}

While* While::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(condition, "While must have the condition expression");
    condition->accept(v);
    apply(scope, v);
    v->visit(this);
    return this;
}

void Expression::apply(Expression* expression, Visitor* v) {
    while (expression)
        expression = expression->accept(v)->nextExpression;
}

Assign* Assign::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(name, "Assign must have name")
    Id::apply(name, v);
    fassert(value, "Assign must have value")
    Expression::apply(value, v);
    v->visit(this);
    return this;
}

BinaryOp* BinaryOp::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(lhs, "Binary operation must have left side expression")
    lhs->accept(v);
    fassert(rhs, "Binary operation must have right side expression")
    rhs->accept(v);
    v->visit(this);
    return this;
}

Call* Call::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    fassert(name, "Call expression must have name")
    name->accept(v);
    Expression::apply(arguments, v);
    v->visit(this);
    return this;
}

Id* Id::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    return this;
}

void Id::apply(Id* id, Visitor* v) {
    while (id)
        id = id->accept(v)->nextId;
}

Boolean* Boolean::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    return this;
}

Integer* Integer::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    return this;
}

Null* Null::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    return this;
}

Real* Real::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    return this;
}

String* String::accept(Visitor* v) {
    fassert(v, "Visitor is null");
    v->visit(this);
    return this;
}

}

