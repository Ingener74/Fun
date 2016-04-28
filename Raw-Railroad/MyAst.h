#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

class FuncType;
class Expr;
class Import;
class Print;

class MyAst {
public:
    MyAst();
    virtual ~MyAst();

    void parse(std::istream& input, bool debug);

    void importLibrary(Import*);
    void printId(Print*);

    void functionDefinition(FuncType* func);
    void expressionDefinition(Expr* func);

    void addVariable(const std::string& id, int value);

    void printVariable(const std::string& id);

private:
    std::unordered_map<std::string, int> m_variables;
};
