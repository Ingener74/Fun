#include <iostream>

#include "ArgType.h"
#include "FuncType.h"

using namespace std;

FuncType::FuncType(const std::string& id, const std::string& arg) {
    cout << __PRETTY_FUNCTION__ << " " << id << " " << arg << endl;
}

FuncType::FuncType(const std::string& id, ArgType* arg) {
    cout << __PRETTY_FUNCTION__ << " " << id << " " << arg->getId() << endl;
}

FuncType::~FuncType() {
}
