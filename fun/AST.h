#pragma once

#include <map>

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>

#include "location.hh"
#include "Declarations.h"

namespace fun {

class Visitor;
class Statement;
class Expression;

class Pot: public Poco::RefCountedObject {
public:
    using Ptr = Poco::AutoPtr<Pot>;

    Pot() {
    }
    virtual ~Pot() {
    }

    void setRoot(Statement* root);

    Statement* root() {
        return _root;
    }

    const Statement* root() const {
        return _root;
    }

    template<typename T, typename ... Args>
    T *add(Args &&... args) {
        statementId++;
        auto res = new T(statementId, std::forward<Args>(args)...);
        _statements.insert(std::make_pair(statementId, res));
        return res;
    }

    void accept(Visitor*);

    Poco::AutoPtr<Statement> getStatement(StatementId statementId) {
        auto stmt = _statements.find(statementId);
        if (stmt == _statements.end()) {
            return nullptr;
        }
        return stmt->second;
    }

    template<typename T>
    T* getStatement(StatementId statementId) {
        return getStatement(statementId).cast<T>();
    }

private:
    Poco::AutoPtr<Statement> _root;
    std::map<StatementId, Poco::AutoPtr<Statement>> _statements;
    StatementId statementId = 0;
};

class Statement : public Poco::RefCountedObject {
public:
    Statement(StatementId statementId);

    Statement(StatementId statementId, const location& loc);

    template<typename ... Ts>
    Statement(StatementId statementId, const location& loc, Ts*... tail) :
            Statement(statementId) {
        addRefs(tail...);
    }

    virtual ~Statement();

    virtual Statement* accept(Visitor*) = 0;

    Statement* nextStatement = nullptr;
    Expression* lastExpression = nullptr;
    location loc;
    StatementId statementId;

    static int counter();
    static void resetCounter();
protected:

    template<typename T>
    void addRefs(T *arg) {
        _members.emplace_back(arg, true);
    }
    template<typename T, typename ... Ts>
    void addRefs(T *head, Ts* ... tail) {
        addRefs(head);
        addRefs(tail...);
    }

    template<typename T>
    static void removeRefs(T* t) {
        if (t)
            t->release();
    }
    template<typename T, typename ... Ts>
    static void removeRefs(T* t, Ts*... ts) {
        removeRefs(t);
        removeRefs(ts...);
    }
    std::vector<Poco::AutoPtr<Statement>> _members;
    static int stmtCounter;
};

class Break: public Statement {
public:
    Break(StatementId statementId, const location& loc) :
            Statement(statementId, loc) {
    }
    virtual ~Break() = default;

    virtual Break* accept(Visitor*);
};

class Id;
class Function;

class Class: public Statement {
public:
    Class(StatementId statementId, const location& loc, Id* name, Id* derived, Statement* stmts) :
            Statement(statementId, loc, name, derived, stmts), name(name), derived(derived), stmts(stmts) {
    }
    virtual ~Class() {
    }

    virtual Class* accept(Visitor*);

    Id* name = nullptr;
    Id* derived = nullptr;
    Statement* stmts = nullptr;
};

class Continue: public Statement {
public:
    Continue(StatementId statementId, const location& loc) :
            Statement(statementId, loc) {
    }
    virtual ~Continue() = default;

    virtual Continue* accept(Visitor*);
};

class Exception: public Statement {
public:
    Exception(StatementId statementId, const location& loc, Statement* tryStmts = nullptr, Id* errorClasses = nullptr, Id* errorObject = nullptr,
            Statement* catchStmts = nullptr) :
            Statement(statementId, loc, tryStmts, errorClasses, errorObject, catchStmts), tryStmts(tryStmts), errorClasses(
                    errorClasses), errorObject(errorObject), catchStmts(catchStmts) {
    }
    virtual ~Exception() {
    }

    virtual Exception* accept(Visitor*);

    Statement* tryStmts = nullptr;
    Id* errorClasses = nullptr;
    Id* errorObject = nullptr;
    Statement* catchStmts = nullptr;
};

class Expression;

class For: public Statement {
public:
    For(StatementId statementId, const location& loc, Expression* initial = nullptr, Expression* condition = nullptr, Expression* increment =
            nullptr, Statement* stmts = nullptr) :
            Statement(statementId, loc, initial, condition, increment, stmts), initial(initial), condition(condition), increment(
                    increment), stmts(stmts) {
    }
    virtual ~For() {
    }

    virtual For* accept(Visitor*);

    Expression* initial = nullptr, *condition = nullptr, *increment = nullptr;
    Statement* stmts = nullptr;
};

class If: public Statement {
public:
    If(StatementId statementId, const location& loc, Expression* cond, Statement* stmts = nullptr) :
            Statement(statementId, loc, cond, stmts), cond(cond), stmts(stmts) {
    }
    virtual ~If();

    virtual If* accept(Visitor*);

    Expression* cond = nullptr;
    Statement* stmts = nullptr;

    If* nextIf = nullptr;
};

class Ifs: public Statement {
public:
    Ifs(StatementId statementId, const location& loc, If* if_stmts): Statement(statementId, loc, if_stmts), if_stmts(if_stmts){}
    virtual ~Ifs() = default;

    virtual Ifs* accept(Visitor*);

    If* if_stmts = nullptr;
};

class Import: public Statement {
public:
    Import(StatementId statementId, const location& loc, Id* library) :
            Statement(statementId, loc, library), id(library) {
    }
    virtual ~Import() = default;

    virtual Import* accept(Visitor*);

    Id* id = nullptr;
};

class Print: public Statement {
public:
    Print(StatementId statementId, const location& loc, Expression* expr) :
            Statement(statementId, loc, expr), expression(expr) {
    }
    virtual ~Print() = default;

    virtual Print* accept(Visitor*);

    Expression* expression = nullptr;
};

class Return: public Statement {
public:
    Return(StatementId statementId, const location& loc, Expression* expr = nullptr) :
            Statement(statementId, loc, expr), expression(expr) {
    }
    virtual ~Return() = default;

    virtual Return* accept(Visitor*);

    Expression* expression = nullptr;
};

class Throw: public Statement {
public:
    Throw(StatementId statementId, const location& loc, Expression* exression = nullptr) :
            Statement(statementId, loc, exression), expression(exression) {
    }
    virtual ~Throw() = default;

    virtual Throw* accept(Visitor*);

    Expression* expression = nullptr;
};

class While: public Statement {
public:
    While(StatementId statementId, const location& loc, Expression* cond = nullptr, Statement* stmts = nullptr) :
            Statement(statementId, loc, cond, stmts), cond(cond), stmts(stmts) {
    }
    virtual ~While() = default;

    virtual While* accept(Visitor*);

    Expression* cond = nullptr;
    Statement* stmts = nullptr;
};

class Expression: public Statement {
public:
    Expression(StatementId statementId, const location& loc) :
            Statement(statementId, loc) {
    }
    template<typename ... Ts>
    Expression(StatementId statementId, const location& loc, Ts*... members) :
            Statement(statementId, loc, members...) {
    }
    virtual ~Expression();

    virtual Expression* accept(Visitor*) = 0;

    static void apply(Expression*, Visitor*);
    Expression* nextExpression = nullptr;
};

class Assign: public Expression {
public:
    Assign(StatementId statementId, const location& loc, Expression* ids, Expression* exprs, BinaryOperation type = BinaryOperation::Assign) :
            Expression(statementId, loc, ids, exprs), ids(ids), exprs(exprs), type(type) {
    }
    virtual ~Assign();

    virtual Assign* accept(Visitor*);

    BinaryOperation type;
    Expression* ids = nullptr;
    Expression* exprs = nullptr;

    static void apply(Assign*, Visitor*);
    Assign* nextAssign = nullptr;
};

class BinaryOp: public Expression {
public:
    BinaryOp(StatementId statementId, const location& loc, BinaryOperation op, Expression* lhs, Expression* rhs) :
        Expression(statementId, loc, lhs, rhs), m_operation(op), lhs(lhs), rhs(rhs) {
    }
    virtual ~BinaryOp() = default;

    virtual BinaryOp* accept(Visitor*);

    BinaryOperation m_operation;
    Expression* lhs = nullptr, *rhs = nullptr;
};

class Dot : public Expression {
public:
    Dot(StatementId statementId, const location &loc, Expression *lhs, Expression *rhs) : Expression(statementId, loc, lhs, rhs), lhs(lhs), rhs(rhs) {}

    virtual ~Dot() = default;

    virtual Dot *accept(Visitor *);

    Expression *lhs = nullptr, *rhs = nullptr;
};

class Call: public Expression {
public:
    Call(StatementId statementId, const location& loc, Expression* callable, Expression* arg = nullptr) :
        Expression(statementId, loc, callable, arg), callable(callable), arguments(arg) {
    }
    virtual ~Call() = default;

    virtual Call* accept(Visitor*);

    Expression* callable = nullptr;
    Expression* arguments = nullptr;
};

class Dictionary: public Expression {
public:
    Dictionary(StatementId statementId, const location& loc, Assign* assign) :
        Expression(statementId, loc, assign), assign(assign) {
    }
    virtual ~Dictionary() = default;

    virtual Dictionary* accept(Visitor*);

    Assign* assign = nullptr;
};

class Id: public Expression {
public:
    Id(StatementId statementId, const location& loc, const std::string& value) :
        Expression(statementId, loc), value(value) {
    }
    virtual ~Id();

    virtual Id* accept(Visitor*);

    Id* nextId = nullptr;

    std::string value;
};

class Index: public Expression {
public:
    Index(StatementId statementId, const location& loc, Expression* indexable, Expression* arg) :
        Expression(statementId, loc, indexable, arg), indexable(indexable), arg(arg) {
    }
    virtual ~Index() = default;

    virtual Index* accept(Visitor*);

    Expression* indexable = nullptr;
    Expression* arg = nullptr;
};

class RoundBrackets: public Expression {
public:
    RoundBrackets(StatementId statementId, const location& loc, Expression* expr) :
        Expression(statementId, loc, expr), expr(expr) {
    }
    virtual ~RoundBrackets() = default;

    virtual RoundBrackets* accept(Visitor*);

    Expression* expr = nullptr;
};

class Terminal: public Expression {
public:
    Terminal(StatementId statementId, const location& loc) :
            Expression(statementId, loc) {
    }
    template<typename ... Ts>
    Terminal(StatementId statementId, const location& loc, Ts*... members) :
            Expression(statementId, loc, members...) {
    }
    virtual ~Terminal() = default;

    virtual Terminal* accept(Visitor*) = 0;

    virtual Type getType() const {
        return Type::Count;
    }

    virtual std::string toString() const { return ""; }
    virtual bool toBoolean() const { return false; }
    virtual long long toInteger() const { return 0; }
    virtual double toReal() const { return 0.0; }

    static Type getSeniorBinaryOpType(Type lhs, Type rhs);
    static Type getSeniorBinaryOpType(Terminal* lhs, Terminal* rhs);
};

class Function: public Terminal {
public:
    Function(StatementId statementId, const location& loc, Id* id, Id* args = nullptr, Statement* scope = nullptr) :
            Terminal(statementId, loc, id, args, scope), name(id), args(args), stmts(scope) {
    }
    virtual ~Function() = default;

    virtual Function* accept(Visitor*);

    virtual Type getType() const {
        return Type::Function;
    }

    Id* name = nullptr;
    Id* args = nullptr;
    Statement* stmts = nullptr;

    Function* nextFunction = nullptr;
};

class Boolean: public Terminal {
public:
    Boolean(StatementId statementId, const location& loc, bool value) :
            Terminal(statementId, loc), value(value) {
    }
    Boolean(bool value) :
            Terminal(0, location { nullptr, 0, 0 }), value(value) {
    }
    virtual ~Boolean() = default;

    virtual Boolean* accept(Visitor*);

    virtual Type getType() const {
        return Type::Boolean;
    }

    bool value;

    virtual std::string toString() const { return value ? "true" : "false"; }
    virtual bool toBoolean() const { return value; }
    virtual long long toInteger() const { return static_cast<long long>(value); }
    virtual double toReal() const { return static_cast<double>(value); }
};

class Integer: public Terminal {
public:
    Integer(StatementId statementId, const location& loc, long long value) :
            Terminal(statementId, loc), value(value) {
    }
    Integer(long long value) :
            Terminal(0, location{nullptr, 0, 0}), value(value) {
    }
    virtual ~Integer() = default;

    virtual Integer* accept(Visitor* visitor);

    virtual Type getType() const {
        return Type::Integer;
    }

    long long value;

    virtual std::string toString() const;
    virtual bool toBoolean() const { return static_cast<bool>(value); }
    virtual long long toInteger() const { return value; }
    virtual double toReal() const { return static_cast<double>(value); }
};

class Nil: public Terminal {
public:
    Nil(StatementId statementId, const location& loc) :
            Terminal(statementId, loc) {
    }
    Nil() :
            Terminal(0, location { nullptr, 0, 0 }) {
    }
    virtual ~Nil() = default;

    virtual Nil* accept(Visitor*);

    virtual Type getType() const {
        return Type::Nil;
    }

    virtual std::string toString() const { return "nil"; }
    virtual bool toBoolean() const { return false; }
    virtual long long toInteger() const { return 0; }
    virtual double toReal() const { return 0.0; }
};

class Real: public Terminal {
public:
    Real(StatementId statementId, const location& loc, double value) :
            Terminal(statementId, loc), value(value) {
    }
    Real(double value) :
            Terminal(0, location { nullptr, 0, 0 }), value(value) {
    }
    virtual ~Real() = default;

    virtual Real* accept(Visitor* v);

    virtual Type getType() const {
        return Type::Real;
    }

    double value;

    virtual std::string toString() const;
    virtual bool toBoolean() const;
    virtual long long toInteger() const { return static_cast<long long>(value); }
    virtual double toReal() const { return value; }

    static bool isTrue(double);
};

class String: public Terminal {
public:
    String(StatementId statementId, const location& loc, const std::string& value) :
            Terminal(statementId, loc), value(value) {
    }
    String(const std::string& value) :
            Terminal(0, location { nullptr, 0, 0 }), value(value) {
    }
    virtual ~String() = default;

    virtual String* accept(Visitor* v);

    virtual Type getType() const {
        return Type::String;
    }

    std::string value;

    virtual std::string toString() const { return value; }
    virtual bool toBoolean() const { return !value.empty(); }
    virtual long long toInteger() const { return value.size(); }
    virtual double toReal() const { return value.size(); }

    static bool isTrue(const std::string&);
};

}

