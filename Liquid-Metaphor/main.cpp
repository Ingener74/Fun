#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <cxxopts.hpp>

#include <fun.h>

using namespace std;
using namespace fun;

bool parseAndRunCode(Visitor* visitor, istream& inputStream, bool debug) {
    FunLexer lexer(&inputStream);
    FunParser parser(lexer);
    parser.set_debug_level(debug);
    bool result = parser.parse();
    Statement::apply(visitor);
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

        Interpreter interpret;
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
            parseAndRunCode(visitor, file, options.count("debug"));
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
