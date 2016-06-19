#include "Visitor.h"
#include "Nodes.h"

namespace fun {

void Import::accept(Visitor* v) {
    m_import->accept(v);
    v->visit(this);
}

void Scope::accept(Visitor* v) {
    v->visit(this);
    for (auto& n : m_statements)
        n->accept(v);
    v->visit(this);
}

void Return::accept(Visitor* v) {
    if (m_expr)
        m_expr->accept(v);
    v->visit(this);
}

void Print::accept(Visitor* v) {
    m_expr->accept(v);
    v->visit(this);
}

void Function::accept(Visitor* v) {
    m_id->accept(v);
    if (m_args)
        m_args->accept(v);
    if (m_scope)
        m_scope->accept(v);
    v->visit(this);
}

void If::accept(Visitor* v) {
    m_condition->accept(v);
    if (m_elseScope)
        m_elseScope->accept(v);
    if (m_thenScope)
        m_thenScope->accept(v);
    v->visit(this);
}

void While::accept(Visitor* v) {
    m_condition->accept(v);
    m_scope->accept(v);
    v->visit(this);
}

void Id::accept(Visitor* v) {
    v->visit(this);
}

void Assign::accept(Visitor* v) {
    m_id->accept(v);
    m_value->accept(v);
    v->visit(this);
}

void BinaryOp::accept(Visitor* v) {
    m_lhs->accept(v);
    m_rhs->accept(v);
    v->visit(this);
}

void Call::accept(Visitor* v) {
    m_id->accept(v);
    m_arg->accept(v);
    v->visit(this);
}

void Integer::accept(Visitor* v) {
    v->visit(this);
}

void Real::accept(Visitor* v) {
    v->visit(this);
}

void String::accept(Visitor* v) {
    v->visit(this);
}

void Boolean::accept(Visitor* v) {
    v->visit(this);
}

}
