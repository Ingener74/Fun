#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

class Function;
class Expr;
class Import;
class Print;

class Fun1Ast {
public:
    Fun1Ast();
    virtual ~Fun1Ast();

    void parse(std::istream& input, bool debug);

    void compile();

    void run();

    void importLibrary(Import*);
    void printId(Print*);

    void functionDefinition(Function* func);
    void expressionDefinition(Expr* func);

    void addVariable(const std::string& id, int value);

    void printVariable(const std::string& id);

private:
    std::unordered_map<std::string, int> m_variables;
};
