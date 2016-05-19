#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

namespace fun {

class Function;
class Expr;
class Import;
class Print;
class Scope;

class FunAst {
public:
    FunAst();
    virtual ~FunAst();

    void parse(std::istream& input, bool debug);

    void pushScope(Scope*);
    Scope* getScope();

    void importLibrary(Import*);
    void printId(Print*);

    void functionDefinition(Function* func);
    void expressionDefinition(Expr* func);

    void addVariable(const std::string& id, int value);

    void printVariable(const std::string& id);

private:
    std::unordered_map<std::string, int> m_variables;

    Scope* m_scope = nullptr;
};

}
