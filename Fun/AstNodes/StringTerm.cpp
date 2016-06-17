#include "AstVisitors/AstVisitor.h"
#include "AstNodes/StringTerm.h"

namespace fun {

String::String(const std::string& value) :
    m_value(value) {
}

String::~String() {
}

void String::accept(AstVisitor* v) {
    v->visit(this);
}

}
