#include <map>
#include <sstream>
#include <Poco/Thread.h>

#include "AST.h"
#include "Visitor.h"
#include "IOperands.h"
#include "IMemory.h"
#include "debuggers/CommandLineDebugger.h"

namespace fun {

using namespace std;
using namespace Poco;

map<Terminal::Type, string> types {
    {Terminal::Type::Boolean,   "Boolean"},
    {Terminal::Type::String,    "String"},
    {Terminal::Type::Integer,   "Integer"},
    {Terminal::Type::Real,      "Real"},
    {Terminal::Type::Nil,       "Nil"},
    {Terminal::Type::Function,  "Function"},
    {Terminal::Type::Object,    "Object"},
};

CommandLineDebugger::CommandLineDebugger() {
}

CommandLineDebugger::~CommandLineDebugger() {
}

void CommandLineDebugger::onCatchBreakpoint(const Breakpoint&) {
}

void CommandLineDebugger::onOperandsChanged(const std::vector<Terminal*>&) {
}

void CommandLineDebugger::onMemoryChanged(const std::unordered_map<std::string, Terminal*>&) {
}

void CommandLineDebugger::listen(AutoPtr<Visitor> v, AutoPtr<Pot> p) {
    Thread th;
    th.start(*this);

    while (true) {
        vector<string> lastCmd;
        cout << ">>> ";
        string input;
        getline(cin, input);

        stringstream ss;
        ss << input;
        string token;
        vector<string> tokens;
        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            if (lastCmd.empty()) {
                continue;
            } else {
                tokens = lastCmd;
            }
        }

        unordered_map<string, function<int()>> commands {
            {"run",         bind(&CommandLineDebugger::resumeCmd,      this)},
            {"r",           bind(&CommandLineDebugger::resumeCmd,      this)},
            {"si",          bind(&CommandLineDebugger::stepIntoCmd,    this)},
            {"stepin",      bind(&CommandLineDebugger::stepIntoCmd,    this)},
            {"so",          bind(&CommandLineDebugger::stepOverCmd,    this)},
            {"stepover",    bind(&CommandLineDebugger::stepOverCmd,    this)},
            {"ops",         bind(&CommandLineDebugger::operandsCmd,    this)},
            {"operands",    bind(&CommandLineDebugger::operandsCmd,    this)},
            {"vars",        bind(&CommandLineDebugger::memoryCmd,      this)},
            {"variables",   bind(&CommandLineDebugger::memoryCmd,      this)},
            {"breakpoint",  bind(&CommandLineDebugger::breakpointCmd,  this, tokens)},
            {"b",           bind(&CommandLineDebugger::breakpointCmd,  this, tokens)},
            {"quit",        bind(&CommandLineDebugger::quitCmd,        this)},
            {"list",        bind(&CommandLineDebugger::listCmd,        this)},
            {"l",           bind(&CommandLineDebugger::listCmd,        this)},
        };

        auto cmdIt = commands.find(tokens.at(0));
        if (cmdIt == commands.end())
            continue;
        if (cmdIt->second()) {
        } else {
            break;
        }
        lastCmd = tokens;
    }

    if (th.isRunning())
        th.join();
}

void CommandLineDebugger::run() {
    try {
        _pot->accept(_visitor);
    } catch (std::exception &e) {
        cerr << e.what() << endl;
    }
}

int fun::CommandLineDebugger::resumeCmd() {
    resume();
    return 1;
}

int fun::CommandLineDebugger::stepIntoCmd() {
    return 1;
}

int fun::CommandLineDebugger::stepOverCmd() {
    stepOver();
//            list();
    return 1;
}

int fun::CommandLineDebugger::operandsCmd() {
    cout << "########### Operands ###########" << endl;
//    for (auto &i : _operands->getOperands())
//        cout << types[i->getType()] << ": " << i->toString() << endl;
    cout << "################################" << endl;

    return 1;
}

int fun::CommandLineDebugger::memoryCmd() {
    cout << "########### Memory #############" << endl;
//    int indents = 0;
//    for (auto &scope: _memory->getMemory()) {
//        for (auto &var: scope) {
//            cout << [&indents] {
//                stringstream ss;
//                for (int n = 0; n < indents; ++n)
//                    ss << "  ";
//                return ss.str();
//            }() << types[var.second->getType()] << " " << var.first << " == " <<
//                 var.second->toString() << " (" << var.second->referenceCount() << ")" << endl;
//        }
//        indents++;
//    }
    cout << "################################" << endl;
    return 1;
}

int fun::CommandLineDebugger::quitCmd() {
    return 0;
}

int fun::CommandLineDebugger::listCmd() {
//    list();
    return 1;
}

int CommandLineDebugger::breakpointCmd(const std::vector<std::string>& tokens) {
    cout << "breakpoint " << tokens.size() << endl;
    if(tokens.size() < 2)
        throw std::runtime_error("breakpoint command not enough arguments; Usage: b 100");
    stringstream ss;
    ss << tokens[1];
    unsigned int line = 0;
    ss >> line;
    setBreakpoint(line);
    return 1;
}

}
