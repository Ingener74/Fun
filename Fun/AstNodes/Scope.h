#pragma once

#include "AstNode.h"

namespace fun {

class StatementNode;
class AstVisitor;

class Scope: public AstNode {
public:
    Scope(StatementNode* = nullptr);
    virtual ~Scope();

    void accept(AstVisitor*);

    void addStatement(StatementNode*);

    AstVisitor* getResultAstVisitor() {
        return m_resultAstVisitor;
    }

    void setResultAstVisitor(AstVisitor* resultAstVisitor = nullptr) {
        m_resultAstVisitor = resultAstVisitor;
    }

private:
    AstVisitor* m_resultAstVisitor = nullptr;
};

}
