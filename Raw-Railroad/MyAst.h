#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

class MyAst {
public:
    MyAst();
    virtual ~MyAst();

    void parse(std::istream& input);

    void addVariable(const std::string& id, int value);

    void printVariable(const std::string& id);

private:
    std::unordered_map<std::string, int> m_variables;
};
