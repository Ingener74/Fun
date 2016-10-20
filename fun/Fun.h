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

    enum class DebuggerType {
        NoDebugger, NetDebugger, CommandLineDebugger
    };

    static Poco::AutoPtr<Pot> parseString(const std::string& source);
    static Poco::AutoPtr<Pot> parseStream(std::istream& source);
    static Poco::AutoPtr<Pot> parseFile(const std::string& filename);

    void evalString(const std::string& script);
    void evalStream(std::istream& script);
    void evalFile(const std::string& filename);
    void evalAst(Poco::AutoPtr<Pot> pot);

    Fun& setDebugger(DebuggerType);
    Fun& setDebugger(Poco::AutoPtr<Debugger> debugger);
    Poco::AutoPtr<Debugger> getDebugger();

private:
    Poco::AutoPtr<Debugger> _debugger;
    Poco::AutoPtr<Visitor> _visitor;
};

}
