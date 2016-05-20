
#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Args.h"

#include <iostream>

namespace fun {

using namespace std;

Args::Args(const std::string& arg) {
    if(!arg.empty())
        m_args.push_back(arg);
}

Args::~Args() {
}

void Args::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

void Args::addArg(const std::string& arg) {
    m_args.push_back(arg);
}

const std::string& Args::getArg(size_t index) const {
    return m_args.at(index);
}

const std::vector<std::string>& Args::getArgs() const {
    return m_args;
}

}
