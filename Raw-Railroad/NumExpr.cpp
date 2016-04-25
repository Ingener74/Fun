#include <iostream>
#include "NumExpr.h"

using namespace std;

NumExpr::NumExpr(int num) :
    m_num(num) {
    cout << __PRETTY_FUNCTION__ << " " << m_num << endl;
}

NumExpr::~NumExpr() {
    cout << __PRETTY_FUNCTION__ << " " << m_num << endl;
}

