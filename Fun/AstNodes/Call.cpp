#include <AstNodes/ExpressionList.h>
#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Call.h"

namespace fun {

using namespace std;

Call::Call(const std::string& id, ExpressionList* args) :
    m_id(id), m_expressionList(args) {
}

Call::~Call() {
}

void Call::accept(AstVisitor* v) {
    v->visit(this);
    m_expressionList->accept(v);
}

}
