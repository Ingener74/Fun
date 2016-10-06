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
using namespace Poco::Util;

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
    Lexer lexer(filename, &inputStream);
    Ast ast;
    Parser parser(lexer, &ast);
    parser.set_debug_level(debug);
    bool result = parser.parse();
    ast.accept(visitor);
    return result;
}

class FunApplication: public Poco::Util::Application {
public:
    FunApplication() {
    }

protected:
    void initialize(Application& self) {
        Application::initialize(self);
    }

    void uninitialize() {
        Application::uninitialize();
    }

    void reinitialize(Application& self) {
        Application::reinitialize(self);
    }

    void defineOptions(OptionSet& options) {
        Application::defineOptions(options);

        options.addOption(
                Option("help", "h", "help information")
                .required(false)
                .repeatable(false)
                .callback(OptionCallback<FunApplication>(this, &FunApplication::handleHelp)));

        options.addOption(
                Option("debug", "d", "debug mode")
                .required(false)
                .repeatable(false)
                .callback(OptionCallback<FunApplication>(this, &FunApplication::handleDebug)));

        options.addOption(
                Option("file", "f", "input script")
                .required(true)
                .repeatable(false)
                .argument("file", true)
                .callback(OptionCallback<FunApplication>(this, &FunApplication::handleScript)));

        options.addOption(
            Option("watch", "w", "watch for auto reload")
            .callback(OptionCallback<FunApplication>(this, &FunApplication::handleWatch))
        );
    }

    void handleHelp(const std::string& name, const std::string& value) {
        cout << __PRETTY_FUNCTION__ << ", " << name << ": " << value << endl;
    }

    void handleDebug(const std::string& name, const std::string& value) {
        cout << __PRETTY_FUNCTION__ << ", " << name << ": " << value << endl;
    }

    void handleWatch(const std::string& name, const std::string& value) {
        cout << __PRETTY_FUNCTION__ << ", " << name << ": " << value << endl;
    }

    void handleScript(const std::string& name, const std::string& value) {
        scriptFileName = value;
    }

    void displayHelp() {
//        HelpFormatter helpFormatter(options());
//        helpFormatter.setCommand(commandName());
//        helpFormatter.setUsage("OPTIONS");
//        helpFormatter.setHeader(
//                "A sample application that demonstrates some of the features of the Poco::Util::Application class.");
//        helpFormatter.format(std::cout);
    }

    int main(const ArgVec& args) {

        try {
            Printer printer;
            ConsoleDebugger consoleDebugger(&printer);
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
                    parseAndRunCode(visitor, filename, file, false);
                } catch (std::exception &e) {
                    cerr << e.what() << endl;
                }
            });

            if (th.isRunning()) {
                th.join();
            }

            return Application::EXIT_OK;
        } catch (exception const& e) {
            return Application::EXIT_SOFTWARE;
        }
    }

private:
    string scriptFileName;
};

POCO_APP_MAIN(FunApplication)

/*
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
