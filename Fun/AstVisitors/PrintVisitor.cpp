#include <iostream>
#include <sstream>
#include "AstNodes/ArgumentList.h"
#include "AstNodes/ExpressionList.h"
#include "AstNodes/Scope.h"
#include "AstNodes/Statement.h"
#include "AstNodes/Function.h"
#include "AstNodes/If.h"
#include "AstNodes/While.h"
#include "AstNodes/Print.h"
#include "AstNodes/Expression.h"
#include "AstNodes/Assign.h"
#include "AstNodes/BinaryOp.h"
#include "AstNodes/Call.h"
#include "AstNodes/Integer.h"
#include "AstNodes/Import.h"
#include "AstNodes/Id.h"

#include "AstVisitors/PrintVisitor.h"

namespace fun {

using namespace std;

PrintVisitor::PrintVisitor() {
}

PrintVisitor::~PrintVisitor() {
}

void PrintVisitor::visit(ArgumentList* node) {
}

void PrintVisitor::visit(ExpressionList* node) {
}

void PrintVisitor::visit(Scope* node) {
    if (m_scopes.top() == node)
        m_scopes.pop();
    else
        m_scopes.push(node);
}

void PrintVisitor::visit(Function* node) {
}

void PrintVisitor::visit(If* node) {
}

void PrintVisitor::visit(While* node) {
}

void PrintVisitor::visit(Import* node) {
}

void PrintVisitor::visit(Print* node) {
    cout << getTabs() << "print " << endl;
}

void PrintVisitor::visit(Expression* node) {
}

void PrintVisitor::visit(Assign* node) {
    cout << getTabs() << "assign " << endl;
}

void PrintVisitor::visit(BinaryOp* node) {
}

void PrintVisitor::visit(Call* node) {
}

void PrintVisitor::visit(Id* node) {
}

void PrintVisitor::visit(Integer* node) {
}

std::string PrintVisitor::getTabs() const {
    return [=] {stringstream ss; for(size_t i = 0; i < m_scopes.size(); ++i)ss << "    "; return ss.str();}();
}

}

