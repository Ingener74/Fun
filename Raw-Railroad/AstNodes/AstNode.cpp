#include "AstVisitors/AstVisitor.h"
#include "AstNode.h"

namespace fun1 {

AstNode::AstNode() {
}

AstNode::~AstNode() {
}

void AstNode::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

}
