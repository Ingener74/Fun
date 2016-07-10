#include "Visitor.h"
#include "Utils.h"
#include "Nodes.h"

#define ACCEPT(CLASS, BODY)        \
CLASS* CLASS::accept(Visitor* v) { \
    fassert(v, "Visitor is null"); \
    v->visit(this);                \
    BODY                           \
    v->visit(this);                \
    return this;                   \
}

#define ACCEPT_E(CLASS) ACCEPT(CLASS, {})

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

ACCEPT_E(Break)

ACCEPT_E(Continue)

ACCEPT(Exception, {
    Statement::apply(tryStmts, v);
    Id::apply(errorClasses, v);
    Id::apply(errorObject, v);
    Statement::apply(catchStmts, v);
})

ACCEPT(For, {
    Expression::apply(initial, v);
    Expression::apply(condition, v);
    Expression::apply(increment, v);
    Statement::apply(scope, v);
})

ACCEPT(Function, {
    fassert(name, "Function must have the name");
    Id::apply(name, v);
    Expression::apply(args, v);
    Statement::apply(scope, v);
})

ACCEPT(If, {
    fassert(cond, "If must have the condition expression");
    Expression::apply(cond, v);
    Statement::apply(stmts, v);
})

ACCEPT(ElseIf, {
    fassert(cond, "Else If must have the condition expression");
    Expression::apply(cond, v);
    Statement::apply(stmts, v);
})

ACCEPT(Else, {
    Statement::apply(stmts, v);
})

ACCEPT(IfElseIfsElse, {
    fassert(ifStmts, "If Elif Else must have the if statement");
    Statement::apply(ifStmts, v);
    ElseIf::apply(elseIfsStmts, v);
    Statement::apply(elseStmts, v);
})

void ElseIf::apply(ElseIf* elseIf, Visitor* v) {
    while (elseIf)
        elseIf = elseIf->accept(v)->nextElseIf;
}

ACCEPT(Import, {
    fassert(id, "Import must have an id");
    Id::apply(id, v);
})

ACCEPT(Print, {
    fassert(expression, "Print must have the expressions")
    Expression::apply(expression, v);
})

ACCEPT(Return, { Expression::apply(expression, v); })

ACCEPT(Throw, { Expression::apply(expression, v); })

ACCEPT(While, {
    fassert(cond, "While must have the condition expression");
    Expression::apply(cond, v);
    Statement::apply(stmts, v);
})

void Expression::apply(Expression* expression, Visitor* v) {
    while (expression)
        expression = expression->accept(v)->nextExpression;
}

ACCEPT(Assign, {
    fassert(name, "Assign must have name")
    Id::apply(name, v);
    fassert(value, "Assign must have value")
    Expression::apply(value, v);
})

ACCEPT(BinaryOp, {
    fassert(lhs, "Binary operation must have left side expression")
    Expression::apply(lhs, v);
    fassert(rhs, "Binary operation must have right side expression")
    Expression::apply(rhs, v);
})

ACCEPT(Call, {
    fassert(name, "Call expression must have name")
    Id::apply(name, v);
    Expression::apply(arguments, v);
})

ACCEPT_E(Id)

void Id::apply(Id* id, Visitor* v) {
    while (id)
        id = id->accept(v)->nextId;
}

ACCEPT_E(Boolean)

ACCEPT_E(Integer)

ACCEPT_E(Null)

ACCEPT_E(Real)

ACCEPT_E(String)

}

