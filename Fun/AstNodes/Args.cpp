#include "AstNodes/Args.h"

#include <iostream>

namespace fun {

using namespace std;

Args::Args(const std::string& arg) {
    m_args.push_back(arg);
}

Args::~Args() {
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
