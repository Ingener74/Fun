#include <iostream>

#include "IdExpr.h"

using namespace std;

IdExpr::IdExpr(const std::string& id) :
    m_id(id) {
    cout << __PRETTY_FUNCTION__ << " " << m_id << endl;
}

IdExpr::~IdExpr() {
    cout << __PRETTY_FUNCTION__ << " " << m_id << endl;
}

