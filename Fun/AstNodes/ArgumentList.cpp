#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Id.h"
#include "AstNodes/ArgumentList.h"

namespace fun {

using namespace std;

ArgumentList::ArgumentList(Id* arg) {
    if (arg)
        m_args.push_back(arg);
}

ArgumentList::~ArgumentList() {
}

void ArgumentList::accept(AstVisitor* visitor) {
    visitor->visit(this);
}

void ArgumentList::addArg(Id* arg) {
    m_args.push_back(arg);
}

}
