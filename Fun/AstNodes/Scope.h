#pragma once

#include <vector>
#include "AstNode.h"

namespace fun {

class Statement;
class AstVisitor;

class Scope: public AstNode {
public:
    Scope(Statement* = nullptr);
    virtual ~Scope();

    virtual void accept(AstVisitor*);

    void addStatement(Statement*);

    AstVisitor* getResultAstVisitor() {
        return m_resultAstVisitor;
    }

    void setResultAstVisitor(AstVisitor* resultAstVisitor = nullptr) {
        m_resultAstVisitor = resultAstVisitor;
    }

    std::vector<Statement*> m_statements;

private:
    AstVisitor* m_resultAstVisitor = nullptr;

};

}
