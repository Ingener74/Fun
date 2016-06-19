#pragma once

#include <vector>
#include <string>

namespace fun {

class AstVisitor;

class AstNode {
public:
	AstNode() = default;
	virtual ~AstNode() = default;

	virtual void accept(AstVisitor*) = 0;
};

class Statement: public AstNode {
public:
	Statement() = default;
	virtual ~Statement() = default;

	Statement* m_next = nullptr;
};

class Id;

class Import: public Statement {
public:
	Import(Id* library) :
			m_import(library) {
	}
	virtual ~Import() = default;

    virtual void accept(AstVisitor*);

    Id* m_import = nullptr;
};

class Scope: public AstNode {
public:
	Scope(Statement* statement = nullptr) {}
	virtual ~Scope() = default;

	virtual void accept(AstVisitor*);

	std::vector<Statement*> m_statements;
};

class Expression;

class Return: public Statement {
public:
	Return(Expression* expr = nullptr) :
			m_expr(expr) {
	}
	virtual ~Return() = default;

    virtual void accept(AstVisitor*);

    Expression* m_expr = nullptr;
};

class Print: public Statement {
public:
	Print(Expression* expr) :
			m_expr(expr) {
	}
	virtual ~Print() = default;

    virtual void accept(AstVisitor*);

    Expression* m_expr = nullptr;
};

class Function: public Statement {
public:
	Function(Id* id, Id* args = nullptr, Scope* statements = nullptr) :
			m_id(id), m_args(args), m_scope(statements) {
	}
	virtual ~Function() = default;

    virtual void accept(AstVisitor*);

    Id* m_id = nullptr;
    Id* m_args = nullptr;
    Scope* m_scope = nullptr;
};

class If: public Statement {
public:
	If(Expression* condition, Scope* then_scope = nullptr, Scope* else_scope = nullptr) :
		m_condition(condition), m_thenScope(then_scope), m_elseScope(else_scope) {
	}
	virtual ~If() = default;

	void accept(AstVisitor*);

	Expression* m_condition = nullptr;
	Scope* m_thenScope = nullptr, *m_elseScope = nullptr;
};

class While: public Statement {
public:
	While(Expression* condition, Scope* scope) :
		m_condition(condition), m_scope(scope) {
	}
    virtual ~While() = default;

    virtual void accept(AstVisitor*);

    Expression* m_condition = nullptr;
    Scope* m_scope = nullptr;
};

class Declaration: public AstNode {
public:
	Declaration() = default;
	virtual ~Declaration() = default;
};

class Id: public Declaration/*, public Expression*/ {
public:
	Id(const std::string& id) :
			m_id(id) {
	}
	virtual ~Id() = default;

    virtual void accept(AstVisitor*);

    Id* m_next = nullptr;

    std::string m_id;
};

class Expression: public Statement {
public:
	Expression() = default;
	virtual ~Expression() = default;

	Expression* m_next = nullptr;
};

class Assign : public Expression {
public:
	Assign(Id* id, Expression* value) :
			m_id(id), m_value(value) {
	}
	virtual ~Assign() = default;

    virtual void accept(AstVisitor*);

    Id* m_id;
    Expression* m_value;
};

class BinaryOp: public Expression {
public:
    enum Op {
        ADD, ADD_ASSIGN,
        SUB, SUB_ASSIGN,
        MUL, MUL_ASSIGN,
        DIV, DIV_ASSIGN,
        MOD, MOD_ASSIGN,
        MORE, MORE_EQUAL,
        LESS, LESS_EQUAL,
    };

	BinaryOp(Op op, Expression* lhs, Expression* rhs) :
			m_operation(op), m_lhs(lhs), m_rhs(rhs) {
	}
	virtual ~BinaryOp() = default;

    virtual void accept(AstVisitor*);

    Op m_operation;
    Expression* m_lhs = nullptr, *m_rhs = nullptr;
};

class Call: public Expression {
public:
	Call(Id* id, Expression* arg = nullptr) :
			m_id(id), m_arg(arg) {
	}
	virtual ~Call() = default;

    virtual void accept(AstVisitor*);

    Id* m_id = nullptr;
    Expression* m_arg = nullptr;
};

class Terminal: public Expression {
public:
	enum Type {
		Integer, Real, String, Boolean, Class, Function, Unknown,
	};

	Terminal() = default;
	virtual ~Terminal() = default;

	virtual Type getType() const { return Unknown; }
};

class Integer: public Terminal {
public:
	Integer(long long integer) : m_integer(integer) {}
	virtual ~Integer() = default;

	virtual void accept(AstVisitor* visitor);
	virtual Type getType() const { return Terminal::Integer; }

	long long m_integer;
};

class Real: public Terminal {
public:
	Real(double real) : m_real(real) {}
	virtual ~Real() = default;

	virtual void accept(AstVisitor* v);
	virtual Type getType() const { return Terminal::Real; }

	double m_real;
};

class String: public Terminal {
public:
	String(const std::string& value) : m_value(value) {}
	virtual ~String() = default;

	virtual void accept(AstVisitor* v);
	virtual Type getType() const { return Terminal::String; }

	std::string m_value;
};

class Boolean: public Terminal {
public:
	Boolean(bool value) : m_value(value) {}
	virtual ~Boolean() = default;

	virtual void accept(AstVisitor*);
	virtual Type getType() const { return Terminal::Boolean; }

	bool m_value;
};

}
