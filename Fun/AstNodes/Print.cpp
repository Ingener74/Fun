#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Print.h"

namespace fun {

Print::Print(const std::string& id) :
    m_id(id) {
}

Print::~Print() {
}

void Print::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

}
