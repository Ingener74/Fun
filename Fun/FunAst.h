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
class AstVisitor;

class FunAst {
public:
    FunAst();
    virtual ~FunAst();

    void parse(std::istream& input, bool debug);

    void setRoot(Scope*);
    Scope* getRoot();

    AstVisitor* getResultVisitor() {
        return m_resultVisitor;
    }

    void setResultVisitor(AstVisitor* resultVisitor = nullptr) {
        m_resultVisitor = resultVisitor;
    }

private:
    Scope* m_scope = nullptr;
    AstVisitor* m_resultVisitor = nullptr;
};

}
