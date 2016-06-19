#pragma once

#include <istream>
#include <vector>
#include <memory>

namespace fun {

class Node;
class Function;
class Expression;
class Import;
class Print;
class Scope;
class Visitor;

class FunAst {
public:
    FunAst();
    virtual ~FunAst();

    void parse(std::istream& input, bool debug);

    void setRoot(Scope*);
    Scope* getRoot();

    template<typename T, typename ... Args>
    T* createNode(Args&& ... args) {
        std::unique_ptr<T> node(new T(std::forward<Args>(args)...));
        T* result = node.get();
        m_nodes.push_back(std::move(node));
        return result;
    }

private:
    Scope* m_scope = nullptr;

    std::vector<std::unique_ptr<Node>> m_nodes;
};

}
