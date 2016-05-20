#include "AstNodes/Args.h"
#include "AstNodes/ExprList.h"
#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Call.h"

namespace fun {

using namespace std;

Call::Call(const std::string& id, ExprList* args) {
    if (args)
        m_nodes.push_back(args);
}

Call::~Call() {
}

void Call::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

}
