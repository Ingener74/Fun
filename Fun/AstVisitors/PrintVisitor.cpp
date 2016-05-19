#include <iostream>
#include "AstNodes/Import.h"
#include "AstNodes/AssignExpr.h"
#include "AstVisitors/PrintVisitor.h"

namespace fun {

using namespace std;

PrintVisitor::PrintVisitor() {
}

PrintVisitor::~PrintVisitor() {
}

void PrintVisitor::visit(Import* import) {
    cout << "Import " << import->getImport() << endl;
}

void PrintVisitor::visit(AssignExpr* expr) {
    cout << "Assign " << expr->getId() << " = " << expr->getResult() << endl;
}

}
