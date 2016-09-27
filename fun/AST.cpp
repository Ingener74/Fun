#include <sstream>
#include "Visitor.h"
#include "Utils.h"
#include "AST.h"

#define SAFE_RELEASE(x) if (x) x->release();

#define ACCEPT(CLASS, BODY)        \
CLASS* CLASS::accept(Visitor* v) { \
    fassert(v, "Visitor is null"); \
    BODY                           \
    v->visit(this);                \
    return this;                   \
}

namespace fun {

using namespace std;

Ast::~Ast() {
    if(_root)
        _root->release();
    for (auto i: _statements) i->release();
}

void Ast::accept(Visitor* v) {
    v->iterateStatements(_root);
}

int Statement::stmtCounter = 0;

Statement::Statement(const location& loc) :
        loc(loc) {
    stmtCounter++;
}

Statement::~Statement(){
    stmtCounter--;
    SAFE_RELEASE(nextStatement)
}

int Statement::counter() {
    return stmtCounter;
}

ACCEPT(Break, )

ACCEPT(Class, )

Class::~Class() {
    SAFE_RELEASE(name)
    SAFE_RELEASE(derived)
    SAFE_RELEASE(stmts)
}

ACCEPT(Continue, )

ACCEPT(Exception, )

Exception::~Exception(){
    SAFE_RELEASE(tryStmts)
    SAFE_RELEASE(errorClasses)
    SAFE_RELEASE(errorObject)
    SAFE_RELEASE(catchStmts)
}

ACCEPT(For, )

For::~For(){
    SAFE_RELEASE(initial)
    SAFE_RELEASE(condition)
    SAFE_RELEASE(increment)
    SAFE_RELEASE(stmts)
}

ACCEPT(Function, )

Function::~Function(){
    SAFE_RELEASE(name)
    SAFE_RELEASE(args)
    SAFE_RELEASE(stmts)
    SAFE_RELEASE(nextFunction)
}

ACCEPT(Ifs, )

Ifs::~Ifs() {
    SAFE_RELEASE(if_stmts)
}

ACCEPT(If, )

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

ACCEPT(Return, )

Return::~Return(){
    SAFE_RELEASE(expression)
}

ACCEPT(Throw, )

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

ACCEPT(Dot, )

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

ACCEPT(Dictionary, )

Dictionary::~Dictionary(){
    SAFE_RELEASE(assign)
}

ACCEPT(Id, )

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

ACCEPT(RoundBrackets, )

RoundBrackets::~RoundBrackets(){
    SAFE_RELEASE(expr)
}

ACCEPT(Boolean, )

ACCEPT(Integer, )

ACCEPT(Nil, )

ACCEPT(Real, )

ACCEPT(String, )

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
