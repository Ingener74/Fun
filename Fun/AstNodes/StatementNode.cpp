#include "AstVisitors/AstVisitor.h"
#include "AstNodes/StatementNode.h"

namespace fun {

StatementNode::StatementNode() {
}

StatementNode::~StatementNode() {
}

void StatementNode::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

}
