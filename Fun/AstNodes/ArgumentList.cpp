
#include <AstNodes/ArgumentList.h>
#include "AstVisitors/AstVisitor.h"
#include <iostream>

namespace fun {

using namespace std;

ArgumentList::ArgumentList(const std::string& arg) {
    if(!arg.empty())
        m_args.push_back(arg);
}

ArgumentList::~ArgumentList() {
}

void ArgumentList::accept(AstVisitor* visitor) {
    visitor->visit(this);
}

void ArgumentList::addArg(const std::string& arg) {
    m_args.push_back(arg);
}

}
