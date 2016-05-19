#include <iostream>

#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Args.h"
#include "AstNodes/Expr.h"
#include "AstNodes/FunctionStatements.h"
#include "AstNodes/Function.h"

namespace fun {

using namespace std;

Function::Function(const std::string& id, Args* args, FunctionStatements* statements) {
    cout << id << " (";
    for (const auto &i : args->getArgs())
        cout << i << ", ";
    cout << ") {" << endl;
    for (const auto& i : statements->getExpressions())
        cout << "\t" << i->toString() << endl;
    cout << "}" << endl;
}

void Function::accept(AstVisitor* visitor) {
    visitor->visit(this);
    for (auto& n : m_nodes)
        n->accept(visitor);
}

}
