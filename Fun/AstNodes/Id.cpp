#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Id.h"

namespace fun {

using namespace std;

Id::Id(const std::string& id) :
    m_id(id) {
}

Id::~Id() {
}

void Id::accept(AstVisitor* v) {
    v->visit(this);
}

}
