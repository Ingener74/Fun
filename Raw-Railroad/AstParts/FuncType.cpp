#include <iostream>

#include "FuncType.h"

using namespace std;

FuncType::FuncType(const std::string& id) {
    cout << __PRETTY_FUNCTION__ << " " << id << endl;
}

FuncType::~FuncType() {
}

