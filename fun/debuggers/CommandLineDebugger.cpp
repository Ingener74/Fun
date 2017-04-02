#include <sstream>
#include <map>
#include <Poco/Thread.h>

#include "AST.h"
#include "Visitor.h"
#include "IOperands.h"
#include "IMemory.h"
#include "debuggers/CommandLineDebugger.h"

namespace fun {

using namespace std;
using namespace Poco;

map<Type, string> types {
    {Type::Boolean,   "Boolean"},
    {Type::String,    "String"},
    {Type::Integer,   "Integer"},
    {Type::Real,      "Real"},
    {Type::Nil,       "Nil"},
    {Type::Function,  "Function"},
    {Type::Object,    "Object"},
};

CommandLineDebugger::CommandLineDebugger()
    : _commands({
        {"run",         &CommandLineDebugger::resumeCmd      },
        {"r",           &CommandLineDebugger::resumeCmd      },
        {"si",          &CommandLineDebugger::stepIntoCmd    },
        {"stepin",      &CommandLineDebugger::stepIntoCmd    },
        {"so",          &CommandLineDebugger::stepOverCmd    },
        {"stepover",    &CommandLineDebugger::stepOverCmd    },
        {"ops",         &CommandLineDebugger::operandsCmd    },
        {"operands",    &CommandLineDebugger::operandsCmd    },
        {"vars",        &CommandLineDebugger::memoryCmd      },
        {"variables",   &CommandLineDebugger::memoryCmd      },
        {"breakpoint",  &CommandLineDebugger::breakpointCmd  },
        {"b",           &CommandLineDebugger::breakpointCmd  },
        {"quit",        &CommandLineDebugger::quitCmd        },
        {"list",        &CommandLineDebugger::listCmd        },
        {"l",           &CommandLineDebugger::listCmd        },
    })
{
}

CommandLineDebugger::~CommandLineDebugger() {
}

void CommandLineDebugger::onCatchBreakpoint(const Breakpoint&) {
}

void CommandLineDebugger::onOperandsChanged(const std::vector<Terminal*>&) {
}

void CommandLineDebugger::onMemoryChanged(const std::unordered_map<std::string, Terminal*>&) {
}

void CommandLineDebugger::listen(Poco::AutoPtr<Pot>, Poco::AutoPtr<Compiler>, VirtualMachine*) {
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

        auto cmdIt = _commands.find(tokens.at(0));
        if (cmdIt == _commands.end())
            continue;
        if ( (this->*cmdIt->second)(tokens) ) {
        } else {
            break;
        }
        lastCmd = tokens;
    }

    if (th.isRunning())
        th.join();
}

void CommandLineDebugger::onEndProgram() {
}

void CommandLineDebugger::run() {
    try {
        _pot->accept(_visitor);
    } catch (std::exception &e) {
        cerr << e.what() << endl;
    }
}

int fun::CommandLineDebugger::resumeCmd(const std::vector<std::string>& tokens) {
    resume();
    return 1;
}

int fun::CommandLineDebugger::stepIntoCmd(const std::vector<std::string>& tokens) {
    return 1;
}

int fun::CommandLineDebugger::stepOverCmd(const std::vector<std::string>& tokens) {
    stepOver();
//            list();
    return 1;
}

int fun::CommandLineDebugger::operandsCmd(const std::vector<std::string>& tokens) {
    cout << "########### Operands ###########" << endl;
//    for (auto &i : _operands->getOperands())
//        cout << types[i->getType()] << ": " << i->toString() << endl;
    cout << "################################" << endl;

    return 1;
}

int fun::CommandLineDebugger::memoryCmd(const std::vector<std::string>& tokens) {
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

int fun::CommandLineDebugger::quitCmd(const std::vector<std::string>& tokens) {
    return 0;
}

int fun::CommandLineDebugger::listCmd(const std::vector<std::string>& tokens) {
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
