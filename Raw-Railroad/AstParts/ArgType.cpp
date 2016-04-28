#include <iostream>
#include "ArgType.h"

using namespace std;

ArgType::ArgType(const std::string& id) :
    m_id(id) {
    cout << __PRETTY_FUNCTION__ << " " << id << endl;
}

ArgType::~ArgType() {
}

void ArgType::addArg(IdExpr*) {
}
