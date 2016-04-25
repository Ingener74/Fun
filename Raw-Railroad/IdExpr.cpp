#include <iostream>
#include <sstream>

#include "IdExpr.h"

using namespace std;

IdExpr::IdExpr(const std::string& id) :
    m_id(id) {
}

IdExpr::~IdExpr() {
}

std::string IdExpr::toString() const {
    stringstream ss;
    ss << m_id;
    return ss.str();
}
