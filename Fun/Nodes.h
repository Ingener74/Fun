#pragma once

#include <vector>
#include <memory>
#include <string>

namespace fun {

class Visitor;

class Statement {
public:
    Statement() = default;
    virtual ~Statement() = default;

    virtual Statement* accept(Visitor*) = 0;

    template<typename T, typename ... Args>
    static T* make(Args&& ... args) {
        std::unique_ptr<T> node(new T(std::forward<Args>(args)...));
        T* result = node.get();
        statements.push_back(std::move(node));
        return result;
    }

    Statement* nextStatement = nullptr;

    static void clear();
    static void apply(Visitor* v);

    static Statement* entryPoint;
protected:
    static std::vector<std::unique_ptr<Statement>> statements;

    static void apply(Statement* start, Visitor* v);
};

class Break: public Statement {
public:
    Break() = default;
    virtual ~Break() = default;

    virtual Break* accept(Visitor*);
};

class Continue: public Statement {
public:
    Continue() = default;
    virtual ~Continue() = default;

    virtual Continue* accept(Visitor*);
};

class Id;

class Exception: public Statement {
public:
    Exception(Statement* tryStmts = nullptr, Id* errorClasses = nullptr, Id* errorObject = nullptr,
            Statement* catchStmts = nullptr) :
            tryStmts(tryStmts), errorClasses(errorClasses), errorObject(errorObject), catchStmts(catchStmts) {
    }
    virtual ~Exception() = default;

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
            Statement* scope = nullptr) :
            initial(initial), condition(condition), increment(increment), scope(scope) {
    }
    virtual ~For() = default;

    virtual For* accept(Visitor*);

    Expression* initial = nullptr, *condition = nullptr, *increment = nullptr;
    Statement* scope = nullptr;
};

class Function: public Statement {
public:
    Function(Id* id, Id* args = nullptr, Statement* scope = nullptr) :
            name(id), args(args), scope(scope) {
    }
    virtual ~Function() = default;

    virtual Function* accept(Visitor*);

    Id* name = nullptr;
    Id* args = nullptr;
    Statement* scope = nullptr;
};

class ElseIf;

class If: public Statement {
public:
    If(Expression* cond, Statement* thenStmts = nullptr, ElseIf* elseIf = nullptr, Statement* elseStmts = nullptr) :
            cond(cond), thenStmts(thenStmts), elseIf(elseIf), elseStmts(elseStmts) {
    }
    virtual ~If() = default;

    virtual If* accept(Visitor*);

    Expression* cond;
    Statement* thenStmts;
    ElseIf* elseIf;
    Statement* elseStmts;
};

class Import: public Statement {
public:
    Import(Id* library) :
            id(library) {
    }
    virtual ~Import() = default;

    virtual Import* accept(Visitor*);

    Id* id = nullptr;
};

class Print: public Statement {
public:
    Print(Expression* expr) :
            expression(expr) {
    }
    virtual ~Print() = default;

    virtual Print* accept(Visitor*);

    Expression* expression = nullptr;
};

class Return: public Statement {
public:
    Return(Expression* expr = nullptr) :
            expression(expr) {
    }
    virtual ~Return() = default;

    virtual Return* accept(Visitor*);

    Expression* expression = nullptr;
};

class Throw: public Statement {
public:
    Throw(Expression* exression = nullptr) :
            expression(expression) {
    }
    virtual ~Throw() = default;

    virtual Throw* accept(Visitor*);

    Expression* expression = nullptr;
};

class While: public Statement {
public:
    While(Expression* cond = nullptr, Statement* stmts = nullptr) :
            cond(cond), stmts(stmts) {
    }
    virtual ~While() = default;

    virtual While* accept(Visitor*);

    Expression* cond;
    Statement* stmts;
};

class ElseIf: public Statement {
public:
    ElseIf(Expression* cond = nullptr, Statement* stmts = nullptr) :
            cond(cond), stmts(stmts) {
    }
    virtual ~ElseIf() = default;

    virtual ElseIf* accept(Visitor*);

    Expression* cond;
    Statement* stmts;

    static void apply(ElseIf*, Visitor*);
    ElseIf* nextElseIf = nullptr;
};

class Expression: public Statement {
public:
    Expression() = default;
    virtual ~Expression() = default;

    virtual Expression* accept(Visitor*) = 0;

    static void apply(Expression*, Visitor*);
    Expression* nextExpression = nullptr;
};

class Assign: public Expression {
public:
    Assign(Id* id, Expression* value) :
            name(id), value(value) {
    }
    virtual ~Assign() = default;

    virtual Assign* accept(Visitor*);

    Id* name;
    Expression* value;
};

class BinaryOp: public Expression {
public:
    enum Op {
        ADD,
        ADD_ASSIGN,
        SUB,
        SUB_ASSIGN,
        MUL,
        MUL_ASSIGN,
        DIV,
        DIV_ASSIGN,
        MOD,
        MOD_ASSIGN,
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
    virtual ~BinaryOp() = default;

    virtual BinaryOp* accept(Visitor*);

    Op m_operation;
    Expression* lhs = nullptr, *rhs = nullptr;
};

class Call: public Expression {
public:
    Call(Id* id, Expression* arg = nullptr) :
            name(id), arguments(arg) {
    }
    virtual ~Call() = default;

    virtual Call* accept(Visitor*);

    Id* name = nullptr;
    Expression* arguments = nullptr;
};

class Id: public Expression {
public:
    Id(const std::string& value) :
            value(value) {
    }
    virtual ~Id() = default;

    virtual Id* accept(Visitor*);

    Id* nextId = nullptr;

    std::string value;

    static void apply(Id*, Visitor*);
};

class Terminal: public Expression {
public:
    enum Type {
        Integer, Real, String, Boolean, Object, Function, Null, Unknown
    };

    Terminal() = default;
    virtual ~Terminal() = default;

    virtual Terminal* accept(Visitor*) = 0;

    virtual Type getType() const {
        return Unknown;
    }
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
};

class Null: public Terminal {
public:
    Null() = default;
    virtual ~Null() = default;

    virtual Null* accept(Visitor*);

    virtual Type getType() const {
        return Terminal::Null;
    }
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
};

}
