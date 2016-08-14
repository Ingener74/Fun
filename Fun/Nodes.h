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
    Statement();
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
    Break() = default;
    virtual ~Break() = default;

    virtual Break* accept(Visitor*);
};

class Id;
class Function;

class Class: public Statement {
public:
    Class(Id* name, Id* derived, Statement* stmts) :
            name(name), derived(derived), stmts(stmts) {
    }
    virtual ~Class();

    virtual Class* accept(Visitor*);

    Id* name = nullptr;
    Id* derived = nullptr;
    Statement* stmts = nullptr;
};

class Continue: public Statement {
public:
    Continue() = default;
    virtual ~Continue() = default;

    virtual Continue* accept(Visitor*);
};

class Exception: public Statement {
public:
    Exception(Statement* tryStmts = nullptr, Id* errorClasses = nullptr, Id* errorObject = nullptr,
            Statement* catchStmts = nullptr) :
            tryStmts(tryStmts), errorClasses(errorClasses), errorObject(errorObject), catchStmts(catchStmts) {
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
    For(Expression* initial = nullptr, Expression* condition = nullptr, Expression* increment = nullptr,
            Statement* stmts = nullptr) :
            initial(initial), condition(condition), increment(increment), stmts(stmts) {
    }
    virtual ~For();

    virtual For* accept(Visitor*);

    Expression* initial = nullptr, *condition = nullptr, *increment = nullptr;
    Statement* stmts = nullptr;
};

class If: public Statement {
public:
    If(Expression* cond, Statement* stmts = nullptr) :
            cond(cond), stmts(stmts){
    }
    virtual ~If();

    virtual If* accept(Visitor*);

    Expression* cond;
    Statement* stmts;
};

class ElseIf: public Statement {
public:
    ElseIf(Expression* cond = nullptr, Statement* stmts = nullptr) :
            cond(cond), stmts(stmts) {
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
    Else(Statement* stmts = nullptr) :
            stmts(stmts) {
    }
    virtual ~Else();

    virtual Else* accept(Visitor*);

    Statement* stmts;
};

class IfElseIfsElse : public Statement {
public:
    IfElseIfsElse(If* ifStmts = nullptr, ElseIf* elseIfsStmts = nullptr, Else* elseStmts = nullptr) :
            ifStmts(ifStmts), elseIfsStmts(elseIfsStmts), elseStmts(elseStmts) {
    }
    virtual ~IfElseIfsElse();

    virtual IfElseIfsElse* accept(Visitor*);

    If* ifStmts;
    ElseIf* elseIfsStmts;
    Else* elseStmts;
};

class Import: public Statement {
public:
    Import(Id* library) :
            id(library) {
    }
    virtual ~Import();

    virtual Import* accept(Visitor*);

    Id* id = nullptr;
};

class Print: public Statement {
public:
    Print(Expression* expr) :
            expression(expr) {
    }
    virtual ~Print();

    virtual Print* accept(Visitor*);

    Expression* expression = nullptr;
};

class Return: public Statement {
public:
    Return(Expression* expr = nullptr) :
            expression(expr) {
    }
    virtual ~Return();

    virtual Return* accept(Visitor*);

    Expression* expression = nullptr;
};

class Throw: public Statement {
public:
    Throw(Expression* exression = nullptr) :
            expression(exression) {
    }
    virtual ~Throw();

    virtual Throw* accept(Visitor*);

    Expression* expression = nullptr;
};

class While: public Statement {
public:
    While(Expression* cond = nullptr, Statement* stmts = nullptr) :
            cond(cond), stmts(stmts) {
    }
    virtual ~While();

    virtual While* accept(Visitor*);

    Expression* cond;
    Statement* stmts;
};

class Expression: public Statement {
public:
    Expression() = default;
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

    Assign(Expression* ids, Expression* exprs, Type type = ASSIGN) :
            ids(ids), exprs(exprs), type(type) {
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

    BinaryOp(Op op, Expression* lhs, Expression* rhs) :
            m_operation(op), lhs(lhs), rhs(rhs) {
    }
    virtual ~BinaryOp();

    virtual BinaryOp* accept(Visitor*);

    Op m_operation;
    Expression* lhs = nullptr, *rhs = nullptr;
};

class Call: public Expression {
public:
    Call(Expression* callable, Expression* arg = nullptr) :
            callable(callable), arguments(arg) {
    }
    virtual ~Call();

    virtual Call* accept(Visitor*);

    Expression* callable = nullptr;
    Expression* arguments = nullptr;
};

class Dictionary: public Expression {
public:
    Dictionary(Assign* assign) :
            assign(assign) {
    }
    virtual ~Dictionary();

    virtual Dictionary* accept(Visitor*);

    Assign* assign = nullptr;
};

class Id: public Expression {
public:
    Id(const std::string& value) :
            value(value) {
    }
    virtual ~Id();

    virtual Id* accept(Visitor*);

    Id* nextId = nullptr;

    std::string value;
};

class Index: public Expression {
public:
    Index(Expression* indexable, Expression* arg) :
            indexable(indexable), arg(arg) {
    }
    virtual ~Index();

    virtual Index* accept(Visitor*);

    Expression* indexable = nullptr;
    Expression* arg = nullptr;
};

class RoundBrackets: public Expression {
public:
    RoundBrackets(Expression* expr) :
            expr(expr) {
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

    Terminal() = default;
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
    Function(Id* id, Id* args = nullptr, Statement* scope = nullptr) :
            name(id), args(args), stmts(scope) {
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
    Boolean(bool value) :
            value(value) {
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
    Integer(long long value) :
            value(value) {
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
    Nil() = default;
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
    Real(double value) :
            value(value) {
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
    String(const std::string& value) :
            value(value) {
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
