#pragma once

#include <string>

class ArgType;

class FuncType {
public:
    FuncType(const std::string& id, const std::string& arg);
    FuncType(const std::string& id, ArgType*);
    virtual ~FuncType();
};
