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

    virtual void accept(Visitor*) = 0;

    Statement* nextStatement = nullptr;

    template<typename T, typename ... Args>
    static T* make(Args&& ... args) {
        std::unique_ptr<T> node(new T(std::forward<Args>(args)...));
        T* result = node.get();
        statements.push_back(std::move(node));
        return result;
    }

    static Statement* entryPoint;
    static std::vector<std::unique_ptr<Statement>> statements;

    static void clear();

    static int apply(Visitor* v);

protected:
    static int apply(Statement* start, Visitor* v);
};

class Id;

class Import: public Statement {
public:
    Import(Id* library) :
            id(library) {
    }
    virtual ~Import() = default;

    virtual void accept(Visitor*);

    Id* id = nullptr;
};

class Expression;

class Return: public Statement {
public:
    Return(Expression* expr = nullptr) :
            expression(expr) {
    }
    virtual ~Return() = default;

    virtual void accept(Visitor*);

    Expression* expression = nullptr;
};

class Print: public Statement {
public:
    Print(Expression* expr) :
            expression(expr) {
    }
    virtual ~Print() = default;

    virtual void accept(Visitor*);

    Expression* expression = nullptr;
};

class Function: public Statement {
public:
    Function(Id* id, Id* args = nullptr, Statement* scope = nullptr) :
            name(id), args(args), scope(scope) {
    }
    virtual ~Function() = default;

    virtual void accept(Visitor*);

    Id* name = nullptr;
    Id* args = nullptr;
    Statement* scope = nullptr;
};

class If: public Statement {
public:
    If(Expression* condition, Statement* then_scope = nullptr, Statement* else_scope = nullptr) :
            condition(condition), thenScope(then_scope), elseScope(else_scope) {
    }
    virtual ~If() = default;

    void accept(Visitor*);

    Expression* condition = nullptr;
    Statement* thenScope = nullptr, *elseScope = nullptr;
};

class While: public Statement {
public:
    While(Expression* condition, Statement* scope) :
            condition(condition), scope(scope) {
    }
    virtual ~While() = default;

    virtual void accept(Visitor*);

    Expression* condition = nullptr;
    Statement* scope = nullptr;
};

class For: public Statement {
public:
    For(Expression* initial = nullptr, Expression* condition = nullptr, Expression* increment = nullptr,
            Statement* scope = nullptr) :
            initial(initial), condition(condition), increment(increment), scope(scope) {
    }
    virtual ~For() = default;

    virtual void accept(Visitor*);

    Expression* initial = nullptr, *condition = nullptr, *increment = nullptr;
    Statement* scope = nullptr;
};

class Break: public Statement {
public:
    Break() = default;
    virtual ~Break() = default;

    virtual void accept(Visitor*);
};

class Continue: public Statement {
public:
    Continue() = default;
    virtual ~Continue() = default;

    virtual void accept(Visitor*);
};

class Expression: public Statement {
public:
    Expression() = default;
    virtual ~Expression() = default;

    Expression* nextExpression = nullptr;

    static void apply(Expression*, Visitor*);
};

class Id: public Expression {
public:
    Id(const std::string& value) :
            value(value) {
    }
    virtual ~Id() = default;

    virtual void accept(Visitor*);

    Id* nextId = nullptr;

    std::string value;

    static void apply(Id*, Visitor*);
};

class Assign: public Expression {
public:
    Assign(Id* id, Expression* value) :
            name(id), value(value) {
    }
    virtual ~Assign() = default;

    virtual void accept(Visitor*);

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
    };

    BinaryOp(Op op, Expression* lhs, Expression* rhs) :
            m_operation(op), lhs(lhs), rhs(rhs) {
    }
    virtual ~BinaryOp() = default;

    virtual void accept(Visitor*);

    Op m_operation;
    Expression* lhs = nullptr, *rhs = nullptr;
};

class Call: public Expression {
public:
    Call(Id* id, Expression* arg = nullptr) :
            name(id), arguments(arg) {
    }
    virtual ~Call() = default;

    virtual void accept(Visitor*);

    Id* name = nullptr;
    Expression* arguments = nullptr;
};

class Terminal: public Expression {
public:
    enum Type {
        Integer, Real, String, Boolean, Object, Function, Null, Unknown
    };

    Terminal() = default;
    virtual ~Terminal() = default;

    virtual Type getType() const {
        return Unknown;
    }
};

class Integer: public Terminal {
public:
    Integer(long long value) :
            value(value) {
    }
    virtual ~Integer() = default;

    virtual void accept(Visitor* visitor);
    virtual Type getType() const {
        return Terminal::Integer;
    }

    long long value;
};

class Real: public Terminal {
public:
    Real(double value) :
            value(value) {
    }
    virtual ~Real() = default;

    virtual void accept(Visitor* v);
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

    virtual void accept(Visitor* v);
    virtual Type getType() const {
        return Terminal::String;
    }

    std::string value;
};

class Boolean: public Terminal {
public:
    Boolean(bool value) :
            value(value) {
    }
    virtual ~Boolean() = default;

    virtual void accept(Visitor*);
    virtual Type getType() const {
        return Terminal::Boolean;
    }

    bool value;
};

class Null: public Terminal {
public:
    Null() = default;
    virtual ~Null() = default;

    virtual void accept(Visitor*);
    virtual Type getType() const {
        return Terminal::Null;
    }
};

}
