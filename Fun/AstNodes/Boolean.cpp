#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Boolean.h"

namespace fun {

Boolean::Boolean(bool value) :
    m_value(value) {
}

Boolean::~Boolean() {
}

void Boolean::accept(AstVisitor* v) {
    v->visit(this);
}

}
