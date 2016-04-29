#pragma once

#include <string>

class Args;
class FunctionStatements;

class Function {
public:
    Function(const std::string& id, Args*, FunctionStatements*);
    virtual ~Function() = default;
};
