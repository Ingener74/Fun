#include "Printer.h"

#include <iostream>
#include <sstream>
#include "Nodes.h"
#include "Utils.h"

namespace fun {

using namespace std;

Printer::Printer() {
}

Printer::~Printer() {
}

void Printer::visit(Scope* node) {
//    if (m_scopes.empty()) {
//        m_scopes.push(node);
//    } else if (m_scopes.top() == node)
//        m_scopes.pop();
//    else
//        m_scopes.push(node);
}

void Printer::visit(Function* node) {
}

void Printer::visit(If* node) {
}

void Printer::visit(While* node) {
}

void Printer::visit(Import* node) {
}

void Printer::visit(Print* node) {
    cout << getTabs() << "print " << endl;
}

void Printer::visit(Expression* node) {
}

void Printer::visit(Assign* node) {
}

void Printer::visit(BinaryOp* node) {
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

void Printer::visit(Call* node) {
}

void Printer::visit(Id* node) {
}

void Printer::visit(Integer* node) {
    cout << node->m_integer << endl;
}

void Printer::visit(Real* node) {
    cout << node->m_real << endl;
}

void Printer::visit(Boolean* node) {
    cout << std::boolalpha << node->m_value << endl;
}

void Printer::visit(String* node) {
    cout << node->m_value << endl;
}

std::string Printer::getTabs() const {
    return [=] {stringstream ss; for(size_t i = 0; i < m_scopes.size(); ++i)ss << "    "; return ss.str();}();
}

}

