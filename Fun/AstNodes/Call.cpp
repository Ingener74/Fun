#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Id.h"
#include "AstNodes/Expression.h"
#include "AstNodes/Call.h"

namespace fun {

using namespace std;

Call::Call(Id* id, Expression* arg) :
        m_id(id), m_arg(arg) {
}

Call::~Call() {
}

void Call::accept(AstVisitor* v) {
    m_id->accept(v);
    m_arg->accept(v);
    v->visit(this);
}

}
