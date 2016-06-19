#include "AstVisitors/AstVisitor.h"
#include "AstNodes/AstNode.h"

namespace fun {

void Import::accept(AstVisitor* v) {
    m_import->accept(v);
    v->visit(this);
}

void Scope::accept(AstVisitor* v) {
    v->visit(this);
    for (auto& n : m_statements)
        n->accept(v);
    v->visit(this);
}

void Return::accept(AstVisitor* v) {
    if (m_expr)
        m_expr->accept(v);
    v->visit(this);
}

void Print::accept(AstVisitor* v) {
    m_expr->accept(v);
    v->visit(this);
}

void Function::accept(AstVisitor* v) {
    m_id->accept(v);
    if (m_args)
        m_args->accept(v);
    if (m_scope)
        m_scope->accept(v);
    v->visit(this);
}

void If::accept(AstVisitor* v) {
    m_condition->accept(v);
    if (m_elseScope)
        m_elseScope->accept(v);
    if (m_thenScope)
        m_thenScope->accept(v);
    v->visit(this);
}

void While::accept(AstVisitor* v) {
    m_condition->accept(v);
    m_scope->accept(v);
    v->visit(this);
}

void Id::accept(AstVisitor* v) {
    v->visit(this);
}

void Assign::accept(AstVisitor* v) {
    m_id->accept(v);
    m_value->accept(v);
    v->visit(this);
}

void BinaryOp::accept(AstVisitor* v) {
    m_lhs->accept(v);
    m_rhs->accept(v);
    v->visit(this);
}

void Call::accept(AstVisitor* v) {
    m_id->accept(v);
    m_arg->accept(v);
    v->visit(this);
}

void Integer::accept(AstVisitor* v) {
    v->visit(this);
}

void Real::accept(AstVisitor* v) {
    v->visit(this);
}

void String::accept(AstVisitor* v) {
    v->visit(this);
}

void Boolean::accept(AstVisitor* v) {
    v->visit(this);
}

}
