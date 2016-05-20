#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Id.h"
#include "AstNodes/ExpressionList.h"
#include "AstNodes/Call.h"

namespace fun {

using namespace std;

Call::Call(Id* id, ExpressionList* args) :
    m_id(id), m_expressionList(args) {
}

Call::~Call() {
}

void Call::accept(AstVisitor* v) {
    v->visit(this);
    m_id->accept(v);
    m_expressionList->accept(v);
}

}
