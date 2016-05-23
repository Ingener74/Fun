#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Real.h"

namespace fun {

Real::Real(double real) :
    m_real(real) {
}

Real::~Real() {
}

void Real::accept(AstVisitor* v) {
    v->visit(this);
}

}
