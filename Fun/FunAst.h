#pragma once

#include <istream>
#include <vector>
#include <memory>

namespace fun {

class AstNode;
class Function;
class Expression;
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

    template<typename T, typename ... Args>
    T* createNode(Args&& ... args) {
        std::unique_ptr<T> node(new T(std::forward<Args>(args)...));
        m_nodes.push_back(std::move(node));
        return node.get();
    }

private:
    Scope* m_scope = nullptr;
    AstVisitor* m_resultVisitor = nullptr;

    std::vector<std::unique_ptr<AstNode>> m_nodes;
};

}
