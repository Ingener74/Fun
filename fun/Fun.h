#pragma once

#include <Poco/AutoPtr.h>
#include "Lexer.h"
#include "Utils.h"
#include "VirtualMachine.h"
#include "Debugger.h"

namespace fun {

class Pot;
class Compiler;

class Fun {
public:
    Fun();
    virtual ~Fun();

    enum class DebuggerType {
        NoDebugger, NetDebugger, CommandLineDebugger
    };

    Poco::AutoPtr<Pot> parseString(const std::string& source);
    Poco::AutoPtr<Pot> parseStream(std::istream& source);
    Poco::AutoPtr<Pot> parseFile(const std::string& filename);

    void evalString(const std::string& script);
    void evalStream(std::istream& script);
    void evalFile(const std::string& filename);
    void evalAst(Poco::AutoPtr<Pot> pot);

    Fun& setDebugger(DebuggerType);
    Fun& setDebugger(Poco::AutoPtr<Debugger> debugger);
    Poco::AutoPtr<Debugger> getDebugger();

private:
    std::string _filename;
    Poco::AutoPtr<Debugger> _debugger;
    Poco::AutoPtr<Compiler> _compiler;
    VirtualMachine _virtualMachine;
};

}
