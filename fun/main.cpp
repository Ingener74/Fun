#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <Poco/Thread.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/AbstractConfiguration.h>
#include <Poco/Util/OptionCallback.h>

#include <fun.h>

using namespace std;
using namespace fun;
using namespace Poco;
using namespace Util;

class FunApplication: public Application {
public:
    FunApplication() {
    }

protected:
    void initialize(Application& self) override {
        Application::initialize(self);
    }

    void uninitialize() override {
        Application::uninitialize();
    }

    void reinitialize(Application& self) override {
        Application::reinitialize(self);
    }

    void defineOptions(OptionSet& options) override {
        Application::defineOptions(options);

        options.addOption(
            Option("help", "h", "help information")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<FunApplication>(this, &FunApplication::handleHelp))
        );

        options.addOption(
            Option("debug", "d", "debug mode")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<FunApplication>(this, &FunApplication::handleDebug))
        );

        options.addOption(
            Option("file", "f", "input script")
            .required(false)
            .repeatable(false).argument("file", true)
            .callback(OptionCallback<FunApplication>(this, &FunApplication::handleScript))
        );

        options.addOption(
            Option("print", "p", "Print program")
            .callback(OptionCallback<FunApplication>(this, &FunApplication::handlePrint))
        );

        options.addOption(
            Option("watch", "w", "watch for auto reload")
            .callback(OptionCallback<FunApplication>(this, &FunApplication::handleWatch))
        );
    }

    void handleHelp(const std::string& name, const std::string& value) {
        _help = true;
    }

    void handleDebug(const std::string& name, const std::string& value) {
        _debug = true;
    }

    void handleWatch(const std::string& name, const std::string& value) {
        _watch = true;
    }

    void handlePrint(const std::string& name, const std::string& value) {
        _print = true;
    }

    void handleScript(const std::string& name, const std::string& value) {
        scriptFileName = value;
    }

    int main(const ArgVec& args) override {
        try {
            if (scriptFileName.empty()) {
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

                    // parseAndRunCode(visitor, {}, sourceStream, _debug);

                    sourceStream.clear();
                }
            } else {
                Printer printer;
//                ConsoleDebugger consoleDebugger(&printer);
                Interpreter interpret(nullptr);
                Compiler compiler;

                Visitor* visitor = &interpret;

                string filename = scriptFileName;
                if (scriptFileName.empty())
                    throw std::runtime_error("no input file");
                ifstream file(filename);

                Thread th;
                th.startFunc([visitor, &file, &filename] {
                    try {
//                        parseAndRunCode(visitor, filename, file, false);
                    }
                    catch (std::exception &e) {
                        cerr << e.what() << endl;
                    }
                });

                if (th.isRunning()) {
                    th.join();
                }
            }

            return EXIT_OK;
        } catch (exception const& e) {
            cerr << e.what() << endl;
            return EXIT_SOFTWARE;
        }
    }

private:
    bool _print = false;
    bool _watch = false;
    bool _debug = false;
    bool _help = false;
    string scriptFileName;

    bool parseAndRunCode(Visitor* visitor, const string& filename, istream& inputStream, bool debug) {
        Lexer lexer(filename, &inputStream);
        Pot pot;
        Parser parser(lexer, &pot);
        parser.set_debug_level(debug);
        bool result = parser.parse();
        pot.accept(visitor);
        return result;
    }
};

POCO_APP_MAIN(FunApplication)

/*
int main(int argc, char* argv[]) {
    try {

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

//            if(options.count("debug")) // FIXME
//                consoleDebugger.setBreakpoint({"", 1});

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
                    unsigned int line = 0;
                    ss >> line;
                    consoleDebugger.setBreakpoint(line);
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
*/
