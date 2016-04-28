#include "Function.h"

#include <iostream>

#include "Args.h"
#include "FunctionStatements.h"
#include "Expr.h"

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
