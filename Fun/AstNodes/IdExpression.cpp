#include "AstVisitors/AstVisitor.h"
#include "AstNodes/IdExpression.h"

namespace fun {

using namespace std;

IdExpression::IdExpression(const std::string& id) :
    m_id(id) {
}

IdExpression::~IdExpression() {
}

void IdExpression::accept(AstVisitor* v) {
    v->visit(this);
}

}
