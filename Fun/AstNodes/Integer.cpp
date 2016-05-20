#include <iostream>
#include <sstream>

#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Integer.h"

namespace fun {

using namespace std;

Integer::Integer(int num) :
    m_num(num) {
}

Integer::~Integer() {
}

void Integer::accept(AstVisitor* visitor) {
    visitor->visit(this);
}

}
