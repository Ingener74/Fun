#include <sstream>
#include <cmath>
#include "Visitor.h"
#include "Utils.h"
#include "AST.h"

#define ACCEPT(CLASS, BODY)        \
CLASS* CLASS::accept(Visitor* v) { \
    fassert(v, "Visitor is null"); \
    BODY                           \
    v->visit(this);                \
    return this;                   \
}

namespace fun {

using namespace std;

void Pot::setRoot(Statement* root) {
    _root.assign(root, true);
}

void Pot::accept(Visitor* v) {
    v->iterateStatements(_root);
}

int Statement::stmtCounter = 0;

Statement::Statement() {
    stmtCounter++;
}

Statement::Statement(const location& loc) :
        Statement() {
    this->loc = loc;
}

Statement::~Statement(){
    stmtCounter--;
    removeRefs(nextStatement);

}

int Statement::counter() {
    return stmtCounter;
}

void Statement::resetCounter() {
    stmtCounter = 0;
}

ACCEPT(Break, )

ACCEPT(Class, )

ACCEPT(Continue, )

ACCEPT(Exception, )

ACCEPT(For, )

ACCEPT(Function, )

ACCEPT(Ifs, )

ACCEPT(If, )

If::~If(){
    removeRefs(nextIf);
}

ACCEPT(Import, {
    fassert(id, "Import must have an id");
})

ACCEPT(Print, {
    fassert(expression, "Print must have the expressions")
})

ACCEPT(Return, )

ACCEPT(Throw, )

ACCEPT(While, {
    fassert(cond, "While must have the condition expression");
})

void Expression::apply(Expression* expression, Visitor* v) {
    while (expression)
        expression = expression->accept(v)->nextExpression;
}

Expression::~Expression(){
    removeRefs(nextExpression);
}

ACCEPT(Assign, {
    fassert(ids, "Assign must have name")
    fassert(exprs, "Assign must have value")
})

Assign::~Assign(){
    removeRefs(nextAssign);
}

void Assign::apply(Assign* assign, Visitor* v) {
    while (assign)
        assign = assign->accept(v)->nextAssign;
}

ACCEPT(BinaryOp, {
    fassert(lhs, "Binary operation must have left side expression")
    fassert(rhs, "Binary operation must have right side expression")
})

ACCEPT(Dot, )

ACCEPT(Call, {
    fassert(callable, "Call expression must have name")
})

ACCEPT(Dictionary, )

ACCEPT(Id, )

Id::~Id(){
    removeRefs(nextId);
}

ACCEPT(Index, {
    fassert(indexable, "Index expression must have name")
})

//ACCEPT(ForExpression, {
//})

ACCEPT(RoundBrackets, )

Type Terminal::getSeniorBinaryOpType(Type lhs, Type rhs) {
    fassert(lhs == Type::Nil || lhs == Type::Boolean || lhs == Type::Integer || lhs == Type::Real || lhs == Type::String, "unsupported type");
    fassert(rhs == Type::Nil || rhs == Type::Boolean || rhs == Type::Integer || rhs == Type::Real || rhs == Type::String, "unsupported type");
    return std::max<Type>(lhs, rhs);
}

Type Terminal::getSeniorBinaryOpType(Terminal* lhs, Terminal* rhs) {
    return getSeniorBinaryOpType(lhs->getType(), rhs->getType());
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

bool Real::toBoolean() const {
    return isTrue(value);
}

const double Epsilon = 1e-8;
bool Real::isTrue(double val) {
    return fabs(val) > Epsilon;
}

bool String::isTrue(const std::string& str) {
    return str != "false" && str != "nil" && !str.empty();
}

ACCEPT(AddFrame, )

ACCEPT(RemoveFrame, )

ACCEPT(Jump, )

ACCEPT(ConditionJump, )

}
