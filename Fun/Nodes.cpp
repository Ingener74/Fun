#include <sstream>
#include "Visitor.h"
#include "Utils.h"
#include "Nodes.h"

#define SAFE_RELEASE(x) if (x) x->release();

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
int Statement::stmtCounter = 0;

Statement::Statement(const location& loc) :
        loc(loc) {
    stmtCounter++;
}

Statement::~Statement(){
    stmtCounter--;
    SAFE_RELEASE(nextStatement)
}

void Statement::clear() {
    entryPoint = nullptr;
    entryPoint->release();
}

ACCEPT_E(Break)

ACCEPT(Class, {
    fassert(name, "Class must have the name");
})
Class::~Class() {
    SAFE_RELEASE(name)
    SAFE_RELEASE(derived)
    SAFE_RELEASE(stmts)
}

ACCEPT_E(Continue)

ACCEPT_E(Exception)

Exception::~Exception(){
    SAFE_RELEASE(tryStmts)
    SAFE_RELEASE(errorClasses)
    SAFE_RELEASE(errorObject)
    SAFE_RELEASE(catchStmts)
}

ACCEPT_E(For)

For::~For(){
    SAFE_RELEASE(initial)
    SAFE_RELEASE(condition)
    SAFE_RELEASE(increment)
    SAFE_RELEASE(stmts)
}

ACCEPT_E(Function)

Function::~Function(){
    SAFE_RELEASE(name)
    SAFE_RELEASE(args)
    SAFE_RELEASE(stmts)
    SAFE_RELEASE(nextFunction)
}

ACCEPT_E(Ifs)

Ifs::~Ifs() {
    SAFE_RELEASE(if_stmts)
}

ACCEPT_E(If)

If::~If(){
    SAFE_RELEASE(cond)
    SAFE_RELEASE(stmts)
    SAFE_RELEASE(nextIf)
}

ACCEPT(Import, {
    fassert(id, "Import must have an id");
})

Import::~Import(){
    SAFE_RELEASE(id)
}

ACCEPT(Print, {
    fassert(expression, "Print must have the expressions")
})

Print::~Print(){
    SAFE_RELEASE(expression)
}

ACCEPT_E(Return)

Return::~Return(){
    SAFE_RELEASE(expression)
}

ACCEPT_E(Throw)

Throw::~Throw(){
    SAFE_RELEASE(expression)
}

ACCEPT(While, {
    fassert(cond, "While must have the condition expression");
})

While::~While(){
    SAFE_RELEASE(cond)
    SAFE_RELEASE(stmts)
}

void Expression::apply(Expression* expression, Visitor* v) {
    while (expression)
        expression = expression->accept(v)->nextExpression;
}

Expression::~Expression(){
    SAFE_RELEASE(nextExpression)
}

ACCEPT(Assign, {
    fassert(ids, "Assign must have name")
    fassert(exprs, "Assign must have value")
})

Assign::~Assign(){
    SAFE_RELEASE(ids)
    SAFE_RELEASE(exprs)
    SAFE_RELEASE(nextAssign)
}

void Assign::apply(Assign* assign, Visitor* v) {
    while (assign)
        assign = assign->accept(v)->nextAssign;
}

ACCEPT(BinaryOp, {
    fassert(lhs, "Binary operation must have left side expression")
    fassert(rhs, "Binary operation must have right side expression")
})

BinaryOp::~BinaryOp(){
    SAFE_RELEASE(lhs)
    SAFE_RELEASE(rhs)
}

ACCEPT_E(Dot)

Dot::~Dot() {
    SAFE_RELEASE(lhs)
    SAFE_RELEASE(rhs)
}

ACCEPT(Call, {
    fassert(callable, "Call expression must have name")
})

Call::~Call(){
    SAFE_RELEASE(callable)
    SAFE_RELEASE(arguments)
}

ACCEPT_E(Dictionary)

Dictionary::~Dictionary(){
    SAFE_RELEASE(assign)
}

ACCEPT_E(Id)

Id::~Id(){
    SAFE_RELEASE(nextId)
}

ACCEPT(Index, {
    fassert(indexable, "Index expression must have name")
})

Index::~Index(){
    SAFE_RELEASE(indexable)
    SAFE_RELEASE(arg)
}
//ACCEPT(ForExpression, {
//})

ACCEPT_E(RoundBrackets)

RoundBrackets::~RoundBrackets(){
    SAFE_RELEASE(expr)
}

ACCEPT_E(Boolean)

ACCEPT_E(Integer)

ACCEPT_E(Nil)

ACCEPT_E(Real)

ACCEPT_E(String)

string Integer::toString() const {
    stringstream ss;
    ss << value;
    return ss.str();
}

string Real::toString() const {
    stringstream ss;
    ss << value;
    return ss.str();
}

const double Eps = 1e-6;
bool Real::toBoolean() const {
    return value > Eps;
}

}
