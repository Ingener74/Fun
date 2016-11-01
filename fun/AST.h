#pragma once

#include <vector>
#include <location.hh>

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>

namespace fun {

class Visitor;
class Statement;
class Expression;

enum class BinaryOperation{
    NOP,

    ADD,
    SUB,
    MUL,
    DIV,
    MOD,

    BINARY_OR,
    BINARY_AND,
    BINARY_XOR,
    LOGIC_OR,
    LOGIC_AND,

    LSHIFT,
    RSHIFT,

    LESS,
    MORE,
    LESS_EQUAL,
    MORE_EQUAL,
    EQUAL,
    NOT_EQUAL,
};

class Pot: public Poco::RefCountedObject {
public:
    using Ptr = Poco::AutoPtr<Pot>;

    Pot() {
    }
    virtual ~Pot();

    void setRoot(Statement* root);

    Statement* root() {
        return _root;
    }

    const Statement* root() const {
        return _root;
    }

    template<typename T, typename ... Args>
    T *add(Args &&... args) {
        auto res = new T(std::forward<Args>(args)...);
        _statements.push_back(res);
        return res;
    }

    void accept(Visitor*);

private:
    Poco::AutoPtr<Statement> _root;
    std::vector<Poco::AutoPtr<Statement>> _statements;
};

class Statement : public Poco::RefCountedObject {
public:
    Statement(const location& loc);
    template<typename ... Ts>
    Statement(const location& loc, Ts*... tail) :
            Statement(loc) {
        addRefs(tail...);
    }

    virtual ~Statement();

    virtual Statement* accept(Visitor*) = 0;

    Statement* nextStatement = nullptr;
    Expression* lastExpression = nullptr;
    location loc;

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
        if (t)
            t->release();
        removeRefs(ts...);
    }
    std::vector<Poco::AutoPtr<Statement>> _members;
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
            Statement(loc, name, derived, stmts), name(name), derived(derived), stmts(stmts) {
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
            Statement(loc, tryStmts, errorClasses, errorObject, catchStmts), tryStmts(tryStmts), errorClasses(
                    errorClasses), errorObject(errorObject), catchStmts(catchStmts) {
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
    For(const location& loc, Expression* initial = nullptr, Expression* condition = nullptr, Expression* increment =
            nullptr, Statement* stmts = nullptr) :
            Statement(loc, initial, condition, increment, stmts), initial(initial), condition(condition), increment(
                    increment), stmts(stmts) {
    }
    virtual ~For();

    virtual For* accept(Visitor*);

    Expression* initial = nullptr, *condition = nullptr, *increment = nullptr;
    Statement* stmts = nullptr;
};

class If: public Statement {
public:
    If(const location& loc, Expression* cond, Statement* stmts = nullptr) :
            Statement(loc, cond, stmts), cond(cond), stmts(stmts) {
    }
    virtual ~If();

    virtual If* accept(Visitor*);

    Expression* cond = nullptr;
    Statement* stmts = nullptr;

    If* nextIf = nullptr;
};

class Ifs: public Statement {
public:
    Ifs(const location& loc, If* if_stmts): Statement(loc, if_stmts), if_stmts(if_stmts){}
    virtual ~Ifs();

    virtual Ifs* accept(Visitor*);

    If* if_stmts = nullptr;
};

class Import: public Statement {
public:
    Import(const location& loc, Id* library) :
            Statement(loc, library), id(library) {
    }
    virtual ~Import();

    virtual Import* accept(Visitor*);

    Id* id = nullptr;
};

class Print: public Statement {
public:
    Print(const location& loc, Expression* expr) :
            Statement(loc, expr), expression(expr) {
    }
    virtual ~Print();

    virtual Print* accept(Visitor*);

    Expression* expression = nullptr;
};

class Return: public Statement {
public:
    Return(const location& loc, Expression* expr = nullptr) :
            Statement(loc, expr), expression(expr) {
    }
    virtual ~Return();

    virtual Return* accept(Visitor*);

    Expression* expression = nullptr;
};

class Throw: public Statement {
public:
    Throw(const location& loc, Expression* exression = nullptr) :
            Statement(loc, exression), expression(exression) {
    }
    virtual ~Throw();

    virtual Throw* accept(Visitor*);

    Expression* expression = nullptr;
};

class While: public Statement {
public:
    While(const location& loc, Expression* cond = nullptr, Statement* stmts = nullptr) :
            Statement(loc, cond, stmts), cond(cond), stmts(stmts) {
    }
    virtual ~While();

    virtual While* accept(Visitor*);

    Expression* cond = nullptr;
    Statement* stmts = nullptr;
};

class Expression: public Statement {
public:
    Expression(const location& loc) :
            Statement(loc) {
    }
    template<typename ... Ts>
    Expression(const location& loc, Ts*... members) :
            Statement(loc, members...) {
    }
    virtual ~Expression();

    virtual Expression* accept(Visitor*) = 0;

    static void apply(Expression*, Visitor*);
    Expression* nextExpression = nullptr;
};

class Assign: public Expression {
public:
    Assign(const location& loc, Expression* ids, Expression* exprs, BinaryOperation type = BinaryOperation::NOP) :
            Expression(loc, ids, exprs), ids(ids), exprs(exprs), type(type) {
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
    BinaryOp(const location& loc, BinaryOperation op, Expression* lhs, Expression* rhs) :
        Expression(loc, lhs, rhs), m_operation(op), lhs(lhs), rhs(rhs) {
    }
    virtual ~BinaryOp();

    virtual BinaryOp* accept(Visitor*);

    BinaryOperation m_operation;
    Expression* lhs = nullptr, *rhs = nullptr;
};

class Dot : public Expression {
public:
    Dot(const location &loc, Expression *lhs, Expression *rhs) : Expression(loc, lhs, rhs), lhs(lhs), rhs(rhs) {}

    virtual ~Dot();

    virtual Dot *accept(Visitor *);

    Expression *lhs = nullptr, *rhs = nullptr;
};

class Call: public Expression {
public:
    Call(const location& loc, Expression* callable, Expression* arg = nullptr) :
        Expression(loc, callable, arg), callable(callable), arguments(arg) {
    }
    virtual ~Call();

    virtual Call* accept(Visitor*);

    Expression* callable = nullptr;
    Expression* arguments = nullptr;
};

class Dictionary: public Expression {
public:
    Dictionary(const location& loc, Assign* assign) :
        Expression(loc, assign), assign(assign) {
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
        Expression(loc, indexable, arg), indexable(indexable), arg(arg) {
    }
    virtual ~Index();

    virtual Index* accept(Visitor*);

    Expression* indexable = nullptr;
    Expression* arg = nullptr;
};

class RoundBrackets: public Expression {
public:
    RoundBrackets(const location& loc, Expression* expr) :
        Expression(loc, expr), expr(expr) {
    }
    virtual ~RoundBrackets();

    virtual RoundBrackets* accept(Visitor*);

    Expression* expr = nullptr;
};

class Terminal: public Expression {
public:
    enum Type {
        Unknown,
        Nil, Boolean, Integer, Real, String,
        Object, Function, Dictionary, List
    };

    Terminal(const location& loc) :
            Expression(loc) {
    }
    template<typename ... Ts>
    Terminal(const location& loc, Ts*... members) :
            Expression(loc, members...) {
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

    static Type getSeniorBinaryOpType(Type lhs, Type rhs);
    static Type getSeniorBinaryOpType(Terminal* lhs, Terminal* rhs);
};

class Function: public Terminal {
public:
    Function(const location& loc, Id* id, Id* args = nullptr, Statement* scope = nullptr) :
            Terminal(loc, id, args, scope), name(id), args(args), stmts(scope) {
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

    virtual std::string toString() const { return "nil"; }
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

    static bool isTrue(double);
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

    static bool isTrue(const std::string&);
};

}
