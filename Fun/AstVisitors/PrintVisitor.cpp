#include <iostream>
#include <sstream>
#include "AstNodes/AstNode.h"
#include "Utils.h"
#include "AstVisitors/PrintVisitor.h"

namespace fun {

using namespace std;

PrintVisitor::PrintVisitor() {
}

PrintVisitor::~PrintVisitor() {
}

void PrintVisitor::visit(Scope* node) {
//    if (m_scopes.empty()) {
//        m_scopes.push(node);
//    } else if (m_scopes.top() == node)
//        m_scopes.pop();
//    else
//        m_scopes.push(node);
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
}

void PrintVisitor::visit(BinaryOp* node) {
    fassert(m_terminals.size() >= 2, "not enogth terminals");
    switch (node->m_operation) {
    case BinaryOp::ADD: {
        break;
    }
    case BinaryOp::ADD_ASSIGN: {
        break;
    }
    case BinaryOp::SUB: {
        break;
    }
    case BinaryOp::SUB_ASSIGN: {
        break;
    }
    case BinaryOp::MUL: {
        break;
    }
    case BinaryOp::MUL_ASSIGN: {
        break;
    }
    case BinaryOp::DIV: {
        break;
    }
    case BinaryOp::DIV_ASSIGN: {
        break;
    }
    case BinaryOp::MOD: {
        break;
    }
    case BinaryOp::MOD_ASSIGN: {
        break;
    }
    case BinaryOp::MORE: {
        break;
    }
    case BinaryOp::MORE_EQUAL: {
        break;
    }
    case BinaryOp::LESS: {
        break;
    }
    case BinaryOp::LESS_EQUAL: {
        break;
    }
    }
}

void PrintVisitor::visit(Call* node) {
}

void PrintVisitor::visit(Id* node) {
}

void PrintVisitor::visit(Integer* node) {
    cout << node->m_integer << endl;
}

void PrintVisitor::visit(Real* node) {
    cout << node->m_real << endl;
}

void PrintVisitor::visit(Boolean* node) {
    cout << std::boolalpha << node->m_value << endl;
}

void PrintVisitor::visit(String* node) {
    cout << node->m_value << endl;
}

std::string PrintVisitor::getTabs() const {
    return [=] {stringstream ss; for(size_t i = 0; i < m_scopes.size(); ++i)ss << "    "; return ss.str();}();
}

}

