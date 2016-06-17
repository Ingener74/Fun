#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Integer.h"

namespace fun {

using namespace std;

Integer::Integer(long long integer) :
    m_integer(integer) {
}

Integer::~Integer() {
}

void Integer::accept(AstVisitor* visitor) {
    visitor->visit(this);
}

}
