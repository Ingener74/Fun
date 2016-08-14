#pragma once

#include <vector>
#include <memory>
#include <string>
#include <location.hh>

#include <Poco/RefCountedObject.h>

namespace fun {

class Visitor;

class Statement : public Poco::RefCountedObject {
public:
    Statement(const location& loc);
    virtual ~Statement();

    virtual Statement* accept(Visitor*) = 0;

    Statement* nextStatement = nullptr;
    location loc;

    static int statementCounter(){
        return stmtCounter;
    }

public:
    static Statement* entryPoint;
    static void clear();

    static int stmtCounter;
};

class Break: public Statement {
public:
    Break(const location& loc) :
            Statement(loc) {
    }
    virtual ~Break() = default;

    virtual Break* accept(Visitor*);
};

class Id;
class Function;

class Class: public Statement {
public:
    Class(const location& loc, Id* name, Id* derived, Statement* stmts) :
            Statement(loc), name(name), derived(derived), stmts(stmts) {
    }
    virtual ~Class();

    virtual Class* accept(Visitor*);

    Id* name = nullptr;
    Id* derived = nullptr;
    Statement* stmts = nullptr;
};

class Continue: public Statement {
public:
    Continue(const location& loc) :
            Statement(loc) {
    }
    virtual ~Continue() = default;

    virtual Continue* accept(Visitor*);
};

class Exception: public Statement {
public:
    Exception(const location& loc, Statement* tryStmts = nullptr, Id* errorClasses = nullptr, Id* errorObject = nullptr,
            Statement* catchStmts = nullptr) :
            Statement(loc), tryStmts(tryStmts), errorClasses(errorClasses), errorObject(errorObject), catchStmts(catchStmts) {
    }
    virtual ~Exception();

    virtual Exception* accept(Visitor*);

    Statement* tryStmts = nullptr;
    Id* errorClasses = nullptr;
    Id* errorObject = nullptr;
    Statement* catchStmts = nullptr;
};

class Expression;

class For: public Statement {
public:
    For(const location& loc, Expression* initial = nullptr, Expression* condition = nullptr, Expression* increment = nullptr,
            Statement* stmts = nullptr) :
                Statement(loc), initial(initial), condition(condition), increment(increment), stmts(stmts) {
    }
    virtual ~For();

    virtual For* accept(Visitor*);

    Expression* initial = nullptr, *condition = nullptr, *increment = nullptr;
    Statement* stmts = nullptr;
};

class If: public Statement {
public:
    If(const location& loc, Expression* cond, Statement* stmts = nullptr) :
        Statement(loc), cond(cond), stmts(stmts){
    }
    virtual ~If();

    virtual If* accept(Visitor*);

    Expression* cond;
    Statement* stmts;
};

class ElseIf: public Statement {
public:
    ElseIf(const location& loc, Expression* cond = nullptr, Statement* stmts = nullptr) :
        Statement(loc), cond(cond), stmts(stmts) {
    }
    virtual ~ElseIf();

    virtual ElseIf* accept(Visitor*);

    Expression* cond;
    Statement* stmts;

    static void apply(ElseIf*, Visitor*);
    ElseIf* nextElseIf = nullptr;
};

class Else: public Statement {
public:
    Else(const location& loc, Statement* stmts = nullptr) :
        Statement(loc), stmts(stmts) {
    }
    virtual ~Else();

    virtual Else* accept(Visitor*);

    Statement* stmts;
};

class IfElseIfsElse : public Statement {
public:
    IfElseIfsElse(const location& loc, If* ifStmts = nullptr, ElseIf* elseIfsStmts = nullptr, Else* elseStmts = nullptr) :
        Statement(loc), ifStmts(ifStmts), elseIfsStmts(elseIfsStmts), elseStmts(elseStmts) {
    }
    virtual ~IfElseIfsElse();

    virtual IfElseIfsElse* accept(Visitor*);

    If* ifStmts;
    ElseIf* elseIfsStmts;
    Else* elseStmts;
};

class Import: public Statement {
public:
    Import(const location& loc, Id* library) :
            Statement(loc), id(library) {
    }
    virtual ~Import();

    virtual Import* accept(Visitor*);

    Id* id = nullptr;
};

class Print: public Statement {
public:
    Print(const location& loc, Expression* expr) :
            Statement(loc), expression(expr) {
    }
    virtual ~Print();

    virtual Print* accept(Visitor*);

    Expression* expression = nullptr;
};

class Return: public Statement {
public:
    Return(const location& loc, Expression* expr = nullptr) :
            Statement(loc), expression(expr) {
    }
    virtual ~Return();

    virtual Return* accept(Visitor*);

    Expression* expression = nullptr;
};

class Throw: public Statement {
public:
    Throw(const location& loc, Expression* exression = nullptr) :
            Statement(loc), expression(exression) {
    }
    virtual ~Throw();

    virtual Throw* accept(Visitor*);

    Expression* expression = nullptr;
};

class While: public Statement {
public:
    While(const location& loc, Expression* cond = nullptr, Statement* stmts = nullptr) :
            Statement(loc), cond(cond), stmts(stmts) {
    }
    virtual ~While();

    virtual While* accept(Visitor*);

    Expression* cond;
    Statement* stmts;
};

class Expression: public Statement {
public:
    Expression(const location& loc) :
            Statement(loc) {
    }
    virtual ~Expression();

    virtual Expression* accept(Visitor*) = 0;

    static void apply(Expression*, Visitor*);
    Expression* nextExpression = nullptr;
};

class Assign: public Expression {
public:
    enum Type {
        ASSIGN, ADD, SUB, MUL, DIV, MOD,
    };

    Assign(const location& loc, Expression* ids, Expression* exprs, Type type = ASSIGN) :
            Expression(loc), ids(ids), exprs(exprs), type(type) {
    }
    virtual ~Assign();

    virtual Assign* accept(Visitor*);

    Type type;
    Expression* ids;
    Expression* exprs;

    static void apply(Assign*, Visitor*);
    Assign* nextAssign = nullptr;
};

class BinaryOp: public Expression {
public:
    enum Op {
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,

        MORE,
        MORE_EQUAL,
        LESS,
        LESS_EQUAL,
        EQUAL,
        NOT_EQUAL,
    };

    BinaryOp(const location& loc, Op op, Expression* lhs, Expression* rhs) :
        Expression(loc), m_operation(op), lhs(lhs), rhs(rhs) {
    }
    virtual ~BinaryOp();

    virtual BinaryOp* accept(Visitor*);

    Op m_operation;
    Expression* lhs = nullptr, *rhs = nullptr;
};

class Call: public Expression {
public:
    Call(const location& loc, Expression* callable, Expression* arg = nullptr) :
        Expression(loc), callable(callable), arguments(arg) {
    }
    virtual ~Call();

    virtual Call* accept(Visitor*);

    Expression* callable = nullptr;
    Expression* arguments = nullptr;
};

class Dictionary: public Expression {
public:
    Dictionary(const location& loc, Assign* assign) :
        Expression(loc), assign(assign) {
    }
    virtual ~Dictionary();

    virtual Dictionary* accept(Visitor*);

    Assign* assign = nullptr;
};

class Id: public Expression {
public:
    Id(const location& loc, const std::string& value) :
        Expression(loc), value(value) {
    }
    virtual ~Id();

    virtual Id* accept(Visitor*);

    Id* nextId = nullptr;

    std::string value;
};

class Index: public Expression {
public:
    Index(const location& loc, Expression* indexable, Expression* arg) :
        Expression(loc), indexable(indexable), arg(arg) {
    }
    virtual ~Index();

    virtual Index* accept(Visitor*);

    Expression* indexable = nullptr;
    Expression* arg = nullptr;
};

class RoundBrackets: public Expression {
public:
    RoundBrackets(const location& loc, Expression* expr) :
        Expression(loc), expr(expr) {
    }
    virtual ~RoundBrackets();

    virtual RoundBrackets* accept(Visitor*);

    Expression* expr;
};

class Terminal: public Expression {
public:
    enum Type {
        Integer, Real, String, Boolean, Object, Function, Nil, Unknown
    };

    Terminal(const location& loc) :
            Expression(loc) {
    }
    virtual ~Terminal() = default;

    virtual Terminal* accept(Visitor*) = 0;

    virtual Type getType() const {
        return Unknown;
    }

    virtual std::string toString() const { return ""; }
    virtual bool toBoolean() const { return false; }
    virtual long long toInteger() const { return 0; }
    virtual double toReal() const { return 0.0; }
};

class Function: public Terminal {
public:
    Function(const location& loc, Id* id, Id* args = nullptr, Statement* scope = nullptr) :
            Terminal(loc), name(id), args(args), stmts(scope) {
    }
    virtual ~Function();

    virtual Function* accept(Visitor*);

    virtual Type getType() const {
        return Terminal::Function;
    }

    Id* name = nullptr;
    Id* args = nullptr;
    Statement* stmts = nullptr;

    Function* nextFunction = nullptr;
};

class Boolean: public Terminal {
public:
    Boolean(const location& loc, bool value) :
            Terminal(loc), value(value) {
    }
    Boolean(bool value) :
            Terminal(location { nullptr, 0, 0 }), value(value) {
    }
    virtual ~Boolean() = default;

    virtual Boolean* accept(Visitor*);

    virtual Type getType() const {
        return Terminal::Boolean;
    }

    bool value;

    virtual std::string toString() const { return value ? "true" : "false"; }
    virtual bool toBoolean() const { return value; }
    virtual long long toInteger() const { return static_cast<long long>(value); }
    virtual double toReal() const { return static_cast<double>(value); }
};

class Integer: public Terminal {
public:
    Integer(const location& loc, long long value) :
            Terminal(loc), value(value) {
    }
    Integer(long long value) :
            Terminal(location{nullptr, 0, 0}), value(value) {
    }
    virtual ~Integer() = default;

    virtual Integer* accept(Visitor* visitor);

    virtual Type getType() const {
        return Terminal::Integer;
    }

    long long value;

    virtual std::string toString() const;
    virtual bool toBoolean() const { return static_cast<bool>(value); }
    virtual long long toInteger() const { return value; }
    virtual double toReal() const { return static_cast<double>(value); }
};

class Nil: public Terminal {
public:
    Nil(const location& loc) :
            Terminal(loc) {
    }
    Nil() :
            Terminal(location { nullptr, 0, 0 }) {
    }
    virtual ~Nil() = default;

    virtual Nil* accept(Visitor*);

    virtual Type getType() const {
        return Terminal::Nil;
    }

    virtual std::string toString() const { return ""; }
    virtual bool toBoolean() const { return false; }
    virtual long long toInteger() const { return 0; }
    virtual double toReal() const { return 0.0; }
};

class Real: public Terminal {
public:
    Real(const location& loc, double value) :
            Terminal(loc), value(value) {
    }
    Real(double value) :
            Terminal(location { nullptr, 0, 0 }), value(value) {
    }
    virtual ~Real() = default;

    virtual Real* accept(Visitor* v);

    virtual Type getType() const {
        return Terminal::Real;
    }

    double value;

    virtual std::string toString() const;
    virtual bool toBoolean() const;
    virtual long long toInteger() const { return static_cast<long long>(value); }
    virtual double toReal() const { return value; }
};

class String: public Terminal {
public:
    String(const location& loc, const std::string& value) :
            Terminal(loc), value(value) {
    }
    String(const std::string& value) :
            Terminal(location { nullptr, 0, 0 }), value(value) {
    }
    virtual ~String() = default;

    virtual String* accept(Visitor* v);

    virtual Type getType() const {
        return Terminal::String;
    }

    std::string value;

    virtual std::string toString() const { return value; }
    virtual bool toBoolean() const { return !value.empty(); }
    virtual long long toInteger() const { return value.size(); }
    virtual double toReal() const { return value.size(); }
};

}
