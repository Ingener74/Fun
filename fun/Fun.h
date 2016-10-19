#pragma once

#include <Poco/AutoPtr.h>
#include <Lexer.h>
#include <AST.h>
#include <Printer.h>
#include <Interpreter.h>
#include <Compiler.h>
#include <Utils.h>
#include <Debugger.h>

namespace fun {

class Fun {
public:
    Fun();
    virtual ~Fun();

    enum class Debugger {
        NoDebugger, NetDebugger, CommandLineDebugger, TestingMockDebugger
    };

    Poco::AutoPtr<Pot> parse(const std::string& source);
    Poco::AutoPtr<Pot> parse(const std::istream& source);

    void eval(const std::string& script);
    void eval(const std::istream& script);
    void eval(const Poco::AutoPtr<Pot>& pot);

    Fun& setDebugger(Debugger);
//    Poco::AutoPtr<Debugger> getDebugger();

private:
    Poco::AutoPtr<Debugger> _debugger;
    Poco::AutoPtr<Visitor> _visitor;
};

}
