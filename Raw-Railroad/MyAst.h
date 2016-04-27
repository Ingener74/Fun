#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

class FuncType;
class Expr;

class MyAst {
public:
    MyAst();
    virtual ~MyAst();

    void parse(std::istream& input);

    void importLibrary(const std::string& id);

    void functionDefinition(FuncType* func);
    void expressionDefinition(Expr* func);

    void addVariable(const std::string& id, int value);

    void printVariable(const std::string& id);

private:
    std::unordered_map<std::string, int> m_variables;
};
