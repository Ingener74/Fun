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

#include <Fun.h>

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
                Option("help", "h", "help information").required(false).repeatable(false).callback(
                        OptionCallback<FunApplication>(this, &FunApplication::handleHelp)));

        options.addOption(
                Option("debug", "d", "debug mode").required(false).repeatable(false).callback(
                        OptionCallback<FunApplication>(this, &FunApplication::handleDebug)));

        options.addOption(
                Option("debugger", "D", "debugger: net or command line").callback(
                        OptionCallback<FunApplication>(this, &FunApplication::handleDebugger)));

        options.addOption(
                Option("file", "f", "input script").required(false).repeatable(false).argument("file", true).callback(
                        OptionCallback<FunApplication>(this, &FunApplication::handleScript)));

        options.addOption(
                Option("print", "p", "Print program").callback(
                        OptionCallback<FunApplication>(this, &FunApplication::handlePrint)));

        options.addOption(
                Option("watch", "w", "watch for auto reload").callback(
                        OptionCallback<FunApplication>(this, &FunApplication::handleWatch)));
    }

    void handleHelp(const std::string& name, const std::string& value) {
        _help = true;
    }

    void handleDebug(const std::string& name, const std::string& value) {
        _debug = true;
    }

    void handleDebugger(const std::string& name, const std::string& value) {
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
            Fun fun;
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

                    fun.evalStream(sourceStream);

                    sourceStream.clear();
                }
            } else {
                fun.evalFile(scriptFileName);
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
};

POCO_APP_MAIN(FunApplication)
