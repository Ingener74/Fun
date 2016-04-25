#include <iostream>
#include <sstream>

#include "AssignExpr.h"

using namespace std;

AssignExpr::AssignExpr(const std::string& id, int value) :
    m_id(id), m_value(value) {
}

AssignExpr::~AssignExpr() {
}

std::string AssignExpr::toString() const {
    stringstream ss;
    ss << m_id << " = " << m_value;
    return ss.str();
}
