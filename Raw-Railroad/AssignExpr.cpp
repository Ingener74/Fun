#include <iostream>

#include "AssignExpr.h"

using namespace std;

AssignExpr::AssignExpr(const std::string& id, int value) :
    m_id(id), m_value(value) {
    cout << __PRETTY_FUNCTION__ << " " << m_id << " = " << m_value << endl;
}

AssignExpr::~AssignExpr() {
    cout << __PRETTY_FUNCTION__ << " " << m_id << " = " << m_value << endl;
}

