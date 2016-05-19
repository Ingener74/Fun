#include "AstVisitors/AstVisitor.h"
#include "AstNodes/AstNode.h"

namespace fun {

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
