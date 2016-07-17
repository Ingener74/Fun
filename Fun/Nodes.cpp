#include "Visitor.h"
#include "Utils.h"
#include "Nodes.h"

#define ACCEPT(CLASS, BODY)        \
CLASS* CLASS::accept(Visitor* v) { \
    fassert(v, "Visitor is null"); \
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

ACCEPT_E(Break)

ACCEPT(Class, {
    fassert(name, "Class must have the name");
})

ACCEPT_E(Continue)

ACCEPT_E(Exception)

ACCEPT_E(For)

ACCEPT(Function, {
    fassert(name, "Function must have the name");
})

ACCEPT(If, {
    fassert(cond, "If must have the condition expression");
})

ACCEPT(ElseIf, {
    fassert(cond, "Else If must have the condition expression");
})

ACCEPT_E(Else)

ACCEPT(IfElseIfsElse, {
    fassert(ifStmts, "If Elif Else must have the if statement");
})

void ElseIf::apply(ElseIf* elseIf, Visitor* v) {
    while (elseIf)
        elseIf = elseIf->accept(v)->nextElseIf;
}

ACCEPT(Import, {
    fassert(id, "Import must have an id");
})

ACCEPT(Print, {
    fassert(expression, "Print must have the expressions")
})

ACCEPT_E(Return)

ACCEPT_E(Throw)

ACCEPT(While, {
    fassert(cond, "While must have the condition expression");
})

void Expression::apply(Expression* expression, Visitor* v) {
    while (expression)
        expression = expression->accept(v)->nextExpression;
}

ACCEPT(Assign, {
    fassert(ids, "Assign must have name")
    fassert(exprs, "Assign must have value")
})

void Assign::apply(Assign* assign, Visitor* v) {
    while (assign)
        assign = assign->accept(v)->nextAssign;
}

ACCEPT(BinaryOp, {
    fassert(lhs, "Binary operation must have left side expression")
    fassert(rhs, "Binary operation must have right side expression")
})

ACCEPT(Call, {
    fassert(name, "Call expression must have name")
})

ACCEPT_E(Dictionary)

ACCEPT_E(Id)

void Id::apply(Id* id, Visitor* v) {
    while (id)
        id = id->accept(v)->nextId;
}

ACCEPT_E(RoundBrackets)

ACCEPT_E(Boolean)

ACCEPT_E(Integer)

ACCEPT_E(Nil)

ACCEPT_E(Real)

ACCEPT_E(String)

ACCEPT_E(Self)

std::string Terminal::toString() const {
    return "";
}

bool Terminal::toBoolean() const {
    return false;
}

long long Terminal::toInteger() const {
    return 0;
}

double Terminal::toReal() const {
    return 0;
}

}
