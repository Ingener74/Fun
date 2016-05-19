#include "AstNodes/IdExpr.h"

#include <iostream>
#include <sstream>

namespace fun {

using namespace std;

IdExpression::IdExpression(const std::string& id) :
    m_id(id) {
}

IdExpression::~IdExpression() {
}

std::string IdExpression::toString() const {
    stringstream ss;
    ss << m_id;
    return ss.str();
}

}
