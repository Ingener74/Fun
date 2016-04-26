#pragma once

#include <string>

using namespace std;

class Import {
public:
    Import(const std::string& library);
    virtual ~Import();
};
