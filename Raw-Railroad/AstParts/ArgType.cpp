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

void ArgType::setTest() {
    cout << __PRETTY_FUNCTION__ << " " << m_id << endl;
}
