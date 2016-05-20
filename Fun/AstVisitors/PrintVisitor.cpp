#include <iostream>
#include "AstNodes/Import.h"
#include "AstNodes/Assign.h"
#include "AstVisitors/PrintVisitor.h"

namespace fun {

using namespace std;

PrintVisitor::PrintVisitor() {
}

PrintVisitor::~PrintVisitor() {
}

void PrintVisitor::visit(Import* import) {
    cout << "Import " << import->m_import << endl;
}

void PrintVisitor::visit(Assign* expr) {
    cout << "Assign " << endl;
}

void PrintVisitor::visit(class Print* print) {
    cout << "Print " << endl;
}

}
