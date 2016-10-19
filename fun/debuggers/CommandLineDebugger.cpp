#include <map>
#include <sstream>
#include "AST.h"
#include "IOperands.h"
#include "IMemory.h"
#include "debuggers/CommandLineDebugger.h"

namespace fun {

using namespace std;

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

void CommandLineDebugger::listen() {
    while(true){
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

        auto resumeCmd = [=] {
            resume();
            return 1;
        };

        auto stepIntoCmd = [=] {
            return 1;
        };

        auto stepOverCmd = [=] {
            stepOver();
//            list();
            return 1;
        };

        static map<Terminal::Type, string> types{
                {Terminal::Type::Boolean, "Boolean"},
                {Terminal::Type::String, "String"},
                {Terminal::Type::Integer, "Integer"},
                {Terminal::Type::Real, "Real"},
                {Terminal::Type::Nil, "Nil"},
                {Terminal::Type::Function, "Function"},
                {Terminal::Type::Object, "Object"},
        };
        auto operandsCmd = [&types, this] {

            cout << "########### Operands ###########" << endl;
            for (auto &i: _operands->getOperands()) cout << types[i->getType()] << ": " << i->toString() << endl;
            cout << "################################" << endl;

            return 1;
        };

        auto quitCmd = []{
            return 0;
        };

        auto listCmd = [=]{
    //        consoleDebugger.list();
            return 1;
        };

        auto breakpointCmd = [&tokens, this]{
            cout << "breakpoint " << tokens.size() << endl;
            if(tokens.size() < 2)
                throw std::runtime_error("breakpoint command not enough arguments; Usage: b 100");
            stringstream ss;
            ss << tokens[1];
            unsigned int line = 0;
            ss >> line;
            setBreakpoint(line);
            return 1;
        };

        auto variablesCmd = [=] {
            cout << "########### Memory #############" << endl;
            int indents = 0;
            for (auto &scope: _memory->getMemory()) {
                for (auto &var: scope) {
                    cout << [&indents] {
                        stringstream ss;
                        for (int n = 0; n < indents; ++n)
                            ss << "  ";
                        return ss.str();
                    }() << types[var.second->getType()] << " " << var.first << " == " <<
                         var.second->toString() << " (" << var.second->referenceCount() << ")" << endl;
                }
                indents++;
            }
            cout << "################################" << endl;
            return 1;
        };


        if (tokens.empty())
            if(lastCmd.empty()) {
                continue;
            } else {
                tokens = lastCmd;
            }

        unordered_map<string, function<int()>> commands{
                {"run", resumeCmd},
                {"r", resumeCmd},
                {"si", stepIntoCmd},
                {"stepin", stepIntoCmd},
                {"so", stepOverCmd},
                {"stepover", stepOverCmd},
                {"ops", operandsCmd},
                {"operands", operandsCmd},
                {"vars", variablesCmd},
                {"variables", variablesCmd},
                {"breakpoint", breakpointCmd},
                {"b", breakpointCmd},
                {"quit", quitCmd},
                {"list", listCmd},
                {"l", listCmd},
        };
        auto cmdIt = commands.find(tokens.at(0));
        if(cmdIt == commands.end())
            continue;
        if (cmdIt->second()) {
        } else {
            break;
        }
        lastCmd = tokens;
    }
}

}
