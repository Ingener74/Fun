#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Id.h"
#include "AstNodes/Assign.h"

namespace fun {

using namespace std;

Assign::Assign(Id* id, Expression* value) :
    m_id(id), m_value(value) {
}

Assign::~Assign() {
}

void Assign::accept(AstVisitor* v) {
    v->visit(this);
    m_id->accept(v);
    m_value->accept(v);
}

}
