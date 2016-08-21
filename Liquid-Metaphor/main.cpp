#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <cxxopts.hpp>

#include <Poco/Thread.h>

#include <fun.h>

using namespace std;
using namespace fun;
using namespace Poco;

class ConsoleDebugger : public Debugger {
public:
    ConsoleDebugger(Printer* printer): Debugger(printer) {
    }

    virtual ~ConsoleDebugger() {
    }

    virtual void onOperandsChanged(const std::vector<Terminal*> &operands) override {
    }

    virtual void onMemoryChanged(const std::unordered_map<std::string, Terminal*>& memory) override {
    }

    virtual void onCatchBreakpoint(const Breakpoint &breakpoint) override {
    }
};

bool parseAndRunCode(Visitor* visitor, const string& filename, istream& inputStream, bool debug) {
    Statement* root = nullptr;
    FunLexer lexer(filename, &inputStream);
    FunParser parser(lexer, &root);
    parser.set_debug_level(debug);
    bool result = parser.parse();
    visitor->iterateStatements(root);
    return result;
}

int main(int argc, char* argv[]) {
    try {
        cxxopts::Options options(argv[0], "Fun - command line options");

        options.add_options("")
                ("h,help", "Help")
                ("f,file", "Input file", cxxopts::value<std::string>())
                ("r,run", "Interpret script")
                ("c,compile", "Compile script")
                ("d,debug", "Enable debug");

        options.parse(argc, argv);

        if (options.count("help")) {
            cout << options.help({ "" }) << endl;
        }

        Printer printer;
        ConsoleDebugger consoleDebugger(&printer);
        Interpreter interpret(options.count("debug") ? &consoleDebugger : nullptr);
        Compiler compiler;

        Visitor* visitor = nullptr;

        if (options.count("run"))
            visitor = &interpret;
        else if (options.count("compile"))
            visitor = &compiler;
        else
            visitor = &printer;

        auto& filename = options["file"].as<string>();
        ifstream file(filename);

        if (options.count("file") && file.is_open()) {

            if(options.count("debug"))
                consoleDebugger.setBreakpoint({"", 1});

            Thread th;
            th.startFunc([visitor, &file, &options, &filename]{
                try {
                    parseAndRunCode(visitor, filename, file, false);
                } catch (std::exception &e) {
                    cerr << e.what() << endl;
                }
            });

            static map<Terminal::Type, string> types{
                    {Terminal::Type::Boolean, "Boolean"},
                    {Terminal::Type::String, "String"},
                    {Terminal::Type::Integer, "Integer"},
                    {Terminal::Type::Real, "Real"},
                    {Terminal::Type::Nil, "Nil"},
                    {Terminal::Type::Function, "Function"},
                    {Terminal::Type::Object, "Object"},
            };

            vector<string> lastCmd;
            while(options.count("debug")){
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

                auto run = [&consoleDebugger] {
                    consoleDebugger.resume();
                    return 1;
                };

                auto stepInto = [] {
                    cout << "step into" << endl;
                    return 1;
                };

                auto stepOver = [&consoleDebugger] {
                    consoleDebugger.stepOver();
                    consoleDebugger.list();
                    return 1;
                };

                auto operandsCmd = [&interpret] {

                    cout << "########### Operands ###########" << endl;
                    for (auto &i: interpret.getOperands()) cout << types[i->getType()] << ": " << i->toString() << endl;
                    cout << "################################" << endl;

                    return 1;
                };

                auto quitCmd = []{
                    return 0;
                };

                auto listCmd = [&consoleDebugger]{
                    consoleDebugger.list();
                    return 1;
                };

                auto breakpointCmd = [&tokens, &consoleDebugger]{
                    cout << "breakpoint " << tokens.size() << endl;
                    if(tokens.size() < 2)
                        throw std::runtime_error("breakpoint command not enough arguments; Usage: b 100");
                    stringstream ss;
                    ss << tokens[1];
                    int line = 0;
                    ss >> line;
                    consoleDebugger.setBreakpoint({"", line});
                    return 1;
                };

                auto variablesCmd = [&interpret] {
                    cout << "########### Memory #############" << endl;
                    int indents = 0;
                    for (auto &scope: interpret.getMemory()) {
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

                unordered_map<string, function<int()>> commands{
                        {"run", run},
                        {"r", run},
                        {"si", stepInto},
                        {"stepin", stepInto},
                        {"so", stepOver},
                        {"stepover", stepOver},
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

                if (tokens.empty())
                    if(lastCmd.empty()) {
                        continue;
                    } else {
                        tokens = lastCmd;
                    }
                auto cmdIt = commands.find(tokens.at(0));
                if(cmdIt == commands.end())
                    continue;
                if (cmdIt->second()) {
                } else {
                    break;
                }
                lastCmd = tokens;
            }
            if (th.isRunning()) {
                th.join();
            }
        } else {
            stringstream sourceStream;
            while (true) {
                cout << ">>> ";

                string input;
                getline(cin, input);

                if (input == "quit") {
                    return 0;
                } else if (!input.empty()) {
                    sourceStream << input << endl;
                    continue;
                }

                parseAndRunCode(visitor, {}, sourceStream, options.count("debug"));

                sourceStream.clear();
            }
        }

        return 0;
    } catch (const cxxopts::OptionException& e) {
        cerr << e.what() << endl;
        return 1;
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
}
