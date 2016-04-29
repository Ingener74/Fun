#include <AstNodes/Args.h>
#include <AstNodes/Expr.h>
#include <AstNodes/Function.h>
#include <AstNodes/FunctionStatements.h>
#include <iostream>


using namespace std;

Function::Function(const std::string& id, Args* args,
        FunctionStatements* statements) {
    cout << __PRETTY_FUNCTION__ << " " << id << " (";
    for (const auto &i : args->getArgs())
        cout << i << ", ";
    cout << ") {" << endl;
    for (const auto& i : statements->getExpressions())
        cout << "\t" << i->toString() << endl;
    cout << "}" << endl;
}
