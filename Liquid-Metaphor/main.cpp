#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <cxxopts.hpp>

#include <fun.h>

using namespace std;
using namespace fun;

class ConsoleDebugger: public Debugger{
public:
    ConsoleDebugger() {
    }

    virtual ~ConsoleDebugger() {
    }

    virtual void setBreakpoint(const Breakpoint &breakpoint) override {
    }

    virtual void enableBreakpoint(const Breakpoint &breakpoint) override {
    }

    virtual void disableBreakpoint(const Breakpoint &breakpoint) override {
    }

    virtual void removeBreakpoint(const Breakpoint &breakpoint) override {
    }

    virtual const vector<Breakpoint> &getBreakpoints() const override {
        return vb;
    }

    virtual void pause() override {
    }

    virtual void resume() override {
    }

    virtual void stepOver() override {
        unique_lock<mutex> lock(_mutex);
        _stepOver = true;
        _cond.notify_one();
    }

    virtual void stepIn() override {
    }

    virtual void stepOut() override {
    }

    virtual void onOperandsChanged(const Operands &operands) override {
    }

    virtual void onMemoryChanged(const Memory &memory) override {
    }

    virtual void onCatchBreakpoint(const Breakpoint &breakpoint) override {
    }

    virtual void onBeforeStep() override {
        unique_lock<mutex> lock{_mutex};
        while(!_stepOver)
            _cond.wait(lock);
        _stepOver = false;
    }

    Breakpoints vb;

private:
    bool _stepOver = false;
    mutex _mutex;
    condition_variable _cond;
};

bool parseAndRunCode(Visitor* visitor, istream& inputStream, bool debug) {
    FunLexer lexer(&inputStream);
    FunParser parser(lexer);
    parser.set_debug_level(debug);
    bool result = parser.parse();
    visitor->iterateStatements(Statement::entryPoint);
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

        ConsoleDebugger consoleDebugger;
        Interpreter interpret(options.count("debug") ? &consoleDebugger : nullptr);
        Compiler compiler;
        Printer printer;

        Visitor* visitor = nullptr;

        if (options.count("run"))
            visitor = &interpret;
        else if (options.count("compile"))
            visitor = &compiler;
        else
            visitor = &printer;

        ifstream file(options["file"].as<string>());

        if (options.count("file") && file.is_open()) {

            thread th{[visitor, &file, &options]{
                parseAndRunCode(visitor, file, false/*options.count("debug")*/);
            }};

            static map<Terminal::Type, string> types{
                    {Terminal::Type::Boolean, "Boolean"},
                    {Terminal::Type::String, "String"},
                    {Terminal::Type::Integer, "Integer"},
                    {Terminal::Type::Real, "Real"},
                    {Terminal::Type::Nil, "Nil"},
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

                auto breakpointCmd = [&tokens]{
                    cout << "breakpoint " << tokens.size() << endl;
                    return 1;
                };

                auto variablesCmd = [&interpret]{
                    cout << "########### Memory #############" << endl;
                    for (auto &i: interpret.getMemory()) cout << types[i.second.second->getType()] << " " << i.first << " == " << i.second.second->toString() << " (" << i.second.first << ")" << endl;
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
            if (th.joinable()) {
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

                parseAndRunCode(visitor, sourceStream, options.count("debug"));

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
